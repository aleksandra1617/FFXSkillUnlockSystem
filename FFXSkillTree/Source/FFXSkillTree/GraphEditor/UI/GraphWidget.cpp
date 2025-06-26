#include "GraphWidget.h"
#include "GraphNodeWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UGraphWidget::AddNodeWidget()
{
	if (!GraphCanvas)
		return;
	
	auto NodeWidget = CreateWidget<UGraphNodeWidget>(this, DefaultNodeWidgetClass);
	
	if (!NodeWidget)
		return;

	if (UCanvasPanelSlot* GraphPanelSlot = GraphCanvas->AddChildToCanvas(NodeWidget))
	{
		GraphPanelSlot->SetAutoSize(true);
		GraphPanelSlot->SetPosition(FVector2d(0,0));
	}
}

bool UGraphWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (!InOperation)
		return false;

	if (UUserWidget* DraggedWidget = Cast<UUserWidget>(InOperation->DefaultDragVisual))
	{
		FVector2D LocalPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
		DraggedWidget->RemoveFromParent();
		
		// Add the widget back to the canvas
		UCanvasPanelSlot* GraphPanelSlot = GraphCanvas->AddChildToCanvas(DraggedWidget);
		//UCanvasPanelSlot* GraphPanelSlot =  Cast<UCanvasPanelSlot>(DraggedWidget->Slot);
		
		if (GraphPanelSlot)
		{
			GraphPanelSlot->SetPosition(LocalPosition);
		}

		return true;
	}
	return false;
}
