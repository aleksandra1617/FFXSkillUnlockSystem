// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphNodeWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeClicked, const FGuid&, NodeID);

/**
 * 
 */
UCLASS()
class UGraphNodeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite);
	FGuid NodeID;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnNodeClicked OnNodeClicked;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Graph")
	void SetSelected(bool bSelected);

	UFUNCTION(BlueprintCallable, Category = "Graph")
	bool IsSelected() const { return bIsSelected; }

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> NodeBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> NodeButton;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UFUNCTION()
	void HandleClick();

private: 
	bool bIsSelected = false;
};