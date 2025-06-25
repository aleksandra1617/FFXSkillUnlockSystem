#include "GraphModel.h"

DEFINE_LOG_CATEGORY(GraphModel);

UGraphModel::UGraphModel()
{
	//Temp code to use for testing purposes for now
	auto MakeNode = [](bool bIsTraversable) -> FGraphNodeData
	{
		FGraphNodeData Node;
		Node.ID = FGuid::NewGuid();
		Node.bIsTraversable = bIsTraversable;
		return Node;
	};
	
	// Create nodes
	FGraphNodeData NodeA = MakeNode(true);
	FGraphNodeData NodeB = MakeNode(true);
	FGraphNodeData NodeC = MakeNode(true);
	FGraphNodeData NodeD = MakeNode(true);
	FGraphNodeData NodeE = MakeNode(true);
	FGraphNodeData NodeF = MakeNode(true);
	FGraphNodeData NodeG = MakeNode(true);
	FGraphNodeData NodeH = MakeNode(true);
	
    //Connect
	NodeA.ConnectedNodes = { NodeE.ID, NodeB.ID, NodeG.ID};
	NodeB.ConnectedNodes = { NodeA.ID, NodeF.ID, NodeC.ID, NodeH.ID, NodeG.ID };
	NodeC.ConnectedNodes = { NodeD.ID, NodeB.ID, NodeH.ID };
	NodeD.ConnectedNodes = { NodeE.ID, NodeC.ID };
	NodeE.ConnectedNodes = { NodeA.ID, NodeF.ID, NodeD.ID };
	NodeF.ConnectedNodes = { NodeE.ID, NodeB.ID };
	NodeG.ConnectedNodes = { NodeA.ID, NodeB.ID };
	NodeH.ConnectedNodes = { NodeC.ID, NodeB.ID };
	
	// Add nodes to map (moving them)
	AddNode(MoveTemp(NodeA));
	AddNode(MoveTemp(NodeB));
	AddNode(MoveTemp(NodeC));
	AddNode(MoveTemp(NodeD));
	AddNode(MoveTemp(NodeE));
	AddNode(MoveTemp(NodeF));
	AddNode(MoveTemp(NodeG));
	AddNode(MoveTemp(NodeH));;

	TArray<FGuid> Result = GetReachableNodes(NodeA.ID);

	for (const FGuid& NodeID : Result)
	{
		UE_LOG(LogTemp, Display, TEXT("Reachable Node: %s"), *NodeID.ToString());
	}
}

FGuid UGraphModel::AddNode(FGraphNodeData&& NodeData)
{
	// Assign unique ID if needed
	FGuid NewID = NodeData.ID.IsValid() ? NodeData.ID : FGuid::NewGuid();
	NodeData.ID = NewID;

	// Link back from connected nodes
	for (const FGuid& ConnectedID : NodeData.ConnectedNodes)
	{
		if (FGraphNodeData* OtherNode = AllNodes.Find(ConnectedID))
		{
			OtherNode->ConnectedNodes.AddUnique(NewID);
		}
	}

	// Move node into map (no copy), more memory efficient as no duplicate nodes exist in memory. 
	AllNodes.Add(NewID, MoveTemp(NodeData));
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

TArray<FGuid> UGraphModel::GetReachableNodes(FGuid RootNodeID, int32 MaxDepth)
{
	TArray<FGuid> Path;

	if (!GraphIsValid() || !AllNodes.Contains(RootNodeID))
	{
		return Path;
	}

	TSet<FGuid> Visited;
	TQueue<TPair<FGuid, int32>> SearchQueue;

	SearchQueue.Enqueue(TPair<FGuid, int32>(RootNodeID, 0));
	Visited.Add(RootNodeID);

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
