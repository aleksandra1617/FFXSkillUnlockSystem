// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "GraphModel.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(GraphModel, Log, All);

USTRUCT(BlueprintType)
struct FGraphNodeData
{
	GENERATED_BODY()
	
	/* Will be used when Saving/Loading as FGuid is globally unique. */
	UPROPERTY(VisibleAnywhere)
	FGuid ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGuid> ConnectedNodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTraversable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActivated = false;
};


/**
 * 
 */
UCLASS(Blueprintable)
class FFXSKILLTREE_API UGraphModel : public UObject
{
	GENERATED_BODY()

public:
	UGraphModel();

	UFUNCTION(BlueprintCallable)
	bool GraphIsValid() 
	{
		return StartNodeID.IsValid();
	};
	
	/* Add a new node into the array of nodes so it can be tracked by the graph data model.
	 * This function accepts an rvalue reference, allowing us to MoveTemp() from the call site.
	 */
	FGuid AddNode(FGraphNodeData&& NodeData);
	FGuid AddNode(const TArray<FGuid>& ConnectedTo = TArray<FGuid>(), bool bTraversable = false, const FGuid& NodeID = FGuid());

	/**
	 * Removes a node from the graph by its ID also removes all references to this node from other nodes'
	 * connection lists.
	 *
	 * @param NodeID The unique identifier of the node to remove.
	 * @return true if the node existed and was successfully removed; false otherwise.
	 */
	bool RemoveNode(const FGuid& NodeID);
	
	UFUNCTION(BlueprintCallable)
	TArray<FGuid> GetReachableNodes(FGuid RootNodeID, int32 MaxDepth = 4);

	/////// Getters ///////
	const FGraphNodeData* GetNode(FGuid NodeID) const
	{
		const FGraphNodeData* NodePtr = AllNodes.Find(NodeID);
		return NodePtr;
	};
	
	const FGraphNodeData* GetNodeByID(FGuid NodeID) const
	{
		const FGraphNodeData* NodePtr = AllNodes.Find(NodeID);
		return NodePtr;
	};
	
	const TArray<FGuid> GetAllNodeIDs() const
	{
		TArray<FGuid> Keys;
		AllNodes.GetKeys(Keys);
		return Keys;
	};
	
protected:
	FGuid StartNodeID;
	TMap<FGuid, FGraphNodeData> AllNodes;
};
