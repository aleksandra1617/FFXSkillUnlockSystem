#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphWidget.generated.h"

class UGraphModel;
class UInteractiveGraphDA;
class UCanvasPanel;
class UGraphNodeWidget;
struct FGraphNodeTemplate;

UCLASS()
class FFXSKILLTREE_API UGraphWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGraphNodeWidget> DefaultNodeWidgetClass;

	UPROPERTY(EditAnywhere)
	TMap<FGuid, FVector2D> NodePositions;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
    bool AddNodeWidget();

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> GraphCanvas;

	// Data Only
	FGuid SelectedNodeID;
	TObjectPtr<UGraphModel> GraphModel;
};