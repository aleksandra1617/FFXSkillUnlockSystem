#include "GraphModel.h"

DEFINE_LOG_CATEGORY(GraphModel);

UGraphModel::UGraphModel()
{
	//Temp code to use for testing purposes for now
	// Node A
	FGraphNodeData NodeA;
	NodeA.ID = FGuid::NewGuid();
	NodeA.bIsTraversable = true;

	// Node B
	FGraphNodeData NodeB;
	NodeB.ID = FGuid::NewGuid();
	NodeB.bIsTraversable = true;
	
	// Node C
	FGraphNodeData NodeC;
	NodeC.ID = FGuid::NewGuid();
	NodeC.bIsTraversable = true;

	// Node D
	FGraphNodeData NodeD;
	NodeD.ID = FGuid::NewGuid();
	NodeD.bIsTraversable = true;

	// Node E
	FGraphNodeData NodeE;
	NodeE.ID = FGuid::NewGuid();
	NodeE.bIsTraversable = true;

	// Node F
	FGraphNodeData NodeF;
	NodeF.ID = FGuid::NewGuid();
	NodeF.bIsTraversable = true;

	// Node G
	FGraphNodeData NodeG;
	NodeG.ID = FGuid::NewGuid();
	NodeG.bIsTraversable = true;

	// Node H
	FGraphNodeData NodeH;
	NodeH.ID = FGuid::NewGuid();
	NodeH.bIsTraversable = true;
	
    //Connect
	NodeA.ConnectedNodes = { NodeE.ID, NodeB.ID, NodeG.ID};
	NodeB.ConnectedNodes = { NodeA.ID, NodeF.ID, NodeC.ID, NodeH.ID, NodeG.ID };
	NodeC.ConnectedNodes = { NodeD.ID, NodeB.ID, NodeH.ID };
	NodeD.ConnectedNodes = { NodeE.ID, NodeC.ID };
	NodeE.ConnectedNodes = { NodeA.ID, NodeF.ID, NodeD.ID };
	NodeF.ConnectedNodes = { NodeE.ID, NodeB.ID };
	NodeG.ConnectedNodes = { NodeA.ID, NodeB.ID };
	NodeH.ConnectedNodes = { NodeC.ID, NodeB.ID };
	
	AddNode(&NodeA);
	AddNode(&NodeB);
	AddNode(&NodeC);
	AddNode(&NodeD);
	AddNode(&NodeE);
	AddNode(&NodeF);
	AddNode(&NodeG);
	AddNode(&NodeH);

	TArray<FGuid> Result = GetReachableNodes(NodeA.ID);

	for (const FGuid& NodeID : Result)
	{
		UE_LOG(LogTemp, Display, TEXT("Reachable Node: %s"), *NodeID.ToString());
	}
}

FGuid UGraphModel::AddNode(const FGraphNodeData* NodeData)
{
	if (!NodeData)
	{
		UE_LOG(GraphModel, Warning, TEXT("AddNode: NodeData is null"));
		return FGuid();
	}
	
	FGraphNodeData NewNodeData = *NodeData;

	// Ensure valid UniqueID
	if (!NewNodeData.ID.IsValid())
	{
		NewNodeData.ID = FGuid::NewGuid();

		UE_LOG(GraphModel, Error, TEXT("AddNode: Failed to allocate UGraphNodeData"));
		return FGuid();
	}
	
	// Assign unique ID
	FGuid NewID = NodeData->ID.IsValid() ? NodeData->ID : FGuid::NewGuid();
	NewNodeData.ID = NewID;

	// Ensure the connected nodes have a link to the new node.
	for (const FGuid& ConnectedID : NewNodeData.ConnectedNodes)
	{
		if (FGraphNodeData* OtherNode = AllNodes.Find(ConnectedID))
		{
			OtherNode->ConnectedNodes.AddUnique(NewID);
		}
	}

	// Register node
	AllNodes.Add(NewID, NewNodeData);

	return NewID;
}

FGuid UGraphModel::AddNode(const TArray<FGuid>& ConnectedTo, bool bTraversable, const FGuid& NodeID)
{
	FGraphNodeData NewNodeData;

	// Generate new ID if not provided
	NewNodeData.ID = NodeID.IsValid() ? NodeID : FGuid::NewGuid();
	NewNodeData.bIsTraversable = bTraversable;
	NewNodeData.ConnectedNodes = ConnectedTo;

	// Register node
	AllNodes.Add(NewNodeData.ID, NewNodeData);

	// Ensure the connected nodes have a link to the new node.
	for (const FGuid& OtherID : ConnectedTo)
	{
		if (FGraphNodeData* OtherNode = AllNodes.Find(OtherID))
		{
			if (!OtherNode->ConnectedNodes.Contains(NewNodeData.ID))
			{
				OtherNode->ConnectedNodes.Add(NewNodeData.ID);
			}
		}
	}

	return NewNodeData.ID;
}

bool UGraphModel::RemoveNode(const FGuid& NodeID)
{
	if (!AllNodes.Contains(NodeID))
	{
		return false;
	}

	// Remove references to this node from other nodes' connections
	for (auto& Pair : AllNodes)
	{
		FGraphNodeData NodeData = Pair.Value;
		NodeData.ConnectedNodes.Remove(NodeID);
	}
	
	AllNodes.Remove(NodeID);

	return true;
}

TArray<FGuid> UGraphModel::GetReachableNodes(FGuid StartNodeID, int32 MaxDepth)
{
	TArray<FGuid> Path;

	if (!AllNodes.Contains(StartNodeID))
	{
		return Path;
	}

	TSet<FGuid> Visited;
	TQueue<TPair<FGuid, int32>> SearchQueue;

	SearchQueue.Enqueue(TPair<FGuid, int32>(StartNodeID, 0));
	Visited.Add(StartNodeID);

	while (!SearchQueue.IsEmpty())
	{
		TPair<FGuid, int32> Current;
		SearchQueue.Dequeue(Current);

		FGuid CurrentID = Current.Key;
		int32 Depth = Current.Value;

		if (Depth > MaxDepth)
		{
			continue;
		}
		
		const FGraphNodeData Node = AllNodes[CurrentID];

		if (Node.bIsTraversable && !Node.bIsActivated)
		{
			Path.Add(CurrentID);
		}

		for (const FGuid& NeighborID : Node.ConnectedNodes)
		{
			if (!Visited.Contains(NeighborID) && AllNodes.Contains(NeighborID))
			{
				SearchQueue.Enqueue(TPair<FGuid, int32>(NeighborID, Depth + 1));
				Visited.Add(NeighborID);
			}
		}
	}

	return Path;
}
