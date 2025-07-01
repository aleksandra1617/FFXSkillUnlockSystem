#include "GraphWidget.h"
#include "GraphNodeWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "FFXSkillTree/GraphEditor/GraphModel.h"

void UGraphWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GraphModel = NewObject<UGraphModel>();
}

bool UGraphWidget::AddNodeWidget()
{
	if (!GraphCanvas)
		return false;
	
	auto NodeWidget = CreateWidget<UGraphNodeWidget>(this, DefaultNodeWidgetClass);
	
	if (!NodeWidget)
		return false;

	if (UCanvasPanelSlot* GraphPanelSlot = GraphCanvas->AddChildToCanvas(NodeWidget))
	{
		GraphPanelSlot->SetAutoSize(true);
		GraphPanelSlot->SetPosition(FVector2d(0,0));

		// Adds a node with default values
		if (!GraphModel)
		{
			UE_LOG(LogTemp, Error, TEXT("GraphModel is null!"));
		}
		
		FGuid NodeID = GraphModel->AddNode();
		NodeWidget->NodeID = NodeID;
		NodePositions.Add(NodeID, FVector2d(0,0));

		return true;
	}

	return false;
}

bool UGraphWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (!InOperation)
		return false;

	if (UGraphNodeWidget* DraggedWidget = Cast<UGraphNodeWidget>(InOperation->DefaultDragVisual))
	{
		FVector2D LocalPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
		DraggedWidget->RemoveFromParent();
		
		// Add the widget back to the canvas
		UCanvasPanelSlot* GraphPanelSlot = GraphCanvas->AddChildToCanvas(DraggedWidget);
		
		if (GraphPanelSlot)
		{
			GraphPanelSlot->SetPosition(LocalPosition);
			NodePositions[DraggedWidget->NodeID] = LocalPosition;
		}

		return true;
	}
	return false;
}
