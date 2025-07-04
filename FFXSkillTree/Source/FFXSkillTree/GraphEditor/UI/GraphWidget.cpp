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
		ensureMsgf(GraphModel, TEXT("Attempt to access GraphModel in GraphWidget failed because the GraphModel is null!"));
		
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

	if (UGraphNodeWidget* DraggedWidget = Cast<UGraphNodeWidget>(InOperation->Payload))
	{
		FVector2D LocalPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
		UCanvasPanelSlot* CanSlot = Cast<UCanvasPanelSlot>(DraggedWidget->Slot);

		if (CanSlot)
		{
			CanSlot->SetPosition(LocalPosition);
			NodePositions[DraggedWidget->NodeID] = LocalPosition;
		}
		
		return true;
	}
	
	return false;
}

