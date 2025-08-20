#include "GraphLayoutGenerator.h"
#include "GraphLayoutStrategyBase.h" 
#include "NodePattern.h"            

UNodePattern* UGraphLayoutGenerator::GeneratePattern(TSubclassOf<UGraphLayoutStrategyBase> StrategyClass, int32 NumNodes, float Offset)
{
	if (!StrategyClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No StrategyClass provided."));
		return nullptr;
	}

	UGraphLayoutStrategyBase* Strategy = NewObject<UGraphLayoutStrategyBase>(this, StrategyClass);
	if (!Strategy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create Strategy instance."));
		return nullptr;
	}

	UNodePattern* Pattern = NewObject<UNodePattern>(this);
	Pattern->Points3D = Strategy->GeneratePoints(NumNodes, Offset);
	Pattern->ProjectedPoints.Empty();

	for (const FVector& Point : Pattern->Points3D)
	{
		// Would be good to switch to spawning the nodes at a valid location not always at origin. 
		Pattern->ProjectedPoints.Add(Strategy->ProjectTo2D(Point, FVector2D(0, 0)));
	}

	Pattern->NodeCount = NumNodes;
	Pattern->PatternName = Strategy->LayoutName;

	return Pattern;
}
