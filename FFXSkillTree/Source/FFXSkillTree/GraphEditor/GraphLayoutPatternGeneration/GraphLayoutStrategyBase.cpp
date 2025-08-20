#include "GraphLayoutStrategyBase.h"


TArray<FVector> UGraphLayoutStrategyBase::GeneratePoints(int32 NumNodes, float Offset)
{
	// Default approach
	TArray<FVector> Points;
	
	for (int i = 0; i < NumNodes; ++i)
	{
		Points.Add(FVector(i * Offset, 0.0f, 0.0f));
	}
	
	return Points;
}

TArray<FVector2D> UGraphLayoutStrategyBase::ProjectAllPointsTo2D(TArray<FVector> Points3D, FVector2D CanvasOrigin)
{
	TArray<FVector2D> Points2D;
	
	for (FVector Point : Points3D)
	{
		Points2D.Add(ProjectTo2D(Point, CanvasOrigin));
	}
	
	return Points2D;
}

FVector2D UGraphLayoutStrategyBase::ProjectTo2D(const FVector& Point3D, FVector2D CanvasOrigin)
{
	// Orthographic projection, ignoring Z
	return FVector2D(Point3D.X, Point3D.Y) + CanvasOrigin;
}
