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
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	
	return FReply::Unhandled();
}

void UGraphNodeWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	UDragDropOperation* DragOp = NewObject<UDragDropOperation>();
	DragOp->DefaultDragVisual = this;
	DragOp->Pivot = EDragPivot::MouseDown;
	DragOp->Payload = this;
	OutOperation = DragOp;
}

void UGraphNodeWidget::HandleClick()
{
	OnNodeClicked.Broadcast(NodeID);

	SetSelected(!bIsSelected);
}
