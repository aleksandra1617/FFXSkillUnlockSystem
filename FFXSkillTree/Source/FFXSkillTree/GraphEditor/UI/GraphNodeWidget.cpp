#include "GraphNodeWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/Border.h"

class UCanvasPanelSlot;

void UGraphNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
	SetIsEnabled(true);
	bIsVariable = true;
	SetSelected(false);

	if (NodeButton)
	{
		NodeButton->OnClicked.AddDynamic(this, &UGraphNodeWidget::HandleClick);
	}
}

void UGraphNodeWidget::SetSelected(bool bSelected)
{
	bIsSelected = bSelected;

	if (NodeBorder)
	{
		NodeBorder->SetBrushColor(bIsSelected ? FLinearColor::Blue : FLinearColor::White);
	}
}

FReply UGraphNodeWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return EventReply.NativeReply;
	}
	
	return FReply::Unhandled();
}

void UGraphNodeWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// Hide the original node while dragging
	SetVisibility(ESlateVisibility::Hidden);
	
	UDragDropOperation* DragOp = NewObject<UDragDropOperation>();

	// Create a visual clone of this widget
	if (UWorld* World = GetWorld())
	{
		if (UGraphNodeWidget* DragVisual = CreateWidget<UGraphNodeWidget>(World, GetClass()))
		{
			DragVisual->NodeID = NodeID;
			DragVisual->SetRenderOpacity(0.9f);
			DragOp->DefaultDragVisual = DragVisual;
			DragOp->Pivot = EDragPivot::MouseDown;
		}
	}
	
	DragOp->Payload = this;
	OutOperation = DragOp;
}

void UGraphNodeWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	SetVisibility(ESlateVisibility::Visible);
}

bool UGraphNodeWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	SetVisibility(ESlateVisibility::Visible);
	return true;
}

void UGraphNodeWidget::HandleClick()
{
	OnNodeClicked.Broadcast(NodeID);

	SetSelected(!bIsSelected);
}
