#include "GraphNodeWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

class UCanvasPanelSlot;

void UGraphNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//if (NodeButton)
	//{
		//NodeButton->OnClicked.AddDynamic(this, &UGraphNodeWidget::HandleClick);
	//}

	SetVisibility(ESlateVisibility::Visible);
	SetIsEnabled(true);
	bIsVariable = true;
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
	OutOperation = DragOp;

	// Hide this while dragging
	SetVisibility(ESlateVisibility::HitTestInvisible);

	this->RemoveFromParent();
}

void UGraphNodeWidget::HandleClick()
{
	UE_LOG(LogTemp, Log, TEXT("Node clicked: %s"), *NodeID.ToString());
	OnNodeClicked.Broadcast(NodeID);
}
