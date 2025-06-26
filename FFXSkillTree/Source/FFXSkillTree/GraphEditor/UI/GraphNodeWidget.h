// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphNodeWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeClicked, FGuid, NodeID);

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

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TitleTextBlock;
	
	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<class UButton> NodeButton;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	UFUNCTION()
	void HandleClick();

	virtual bool NativeOnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, UDragDropOperation* Operation) override
	{
		UE_LOG(LogTemp, Warning, TEXT("Drag Over"));
		return true;  
	}
};