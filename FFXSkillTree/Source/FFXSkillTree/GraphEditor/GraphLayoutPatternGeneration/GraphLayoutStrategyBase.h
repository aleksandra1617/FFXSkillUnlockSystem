#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphLayoutStrategyBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class FFXSKILLTREE_API UGraphLayoutStrategyBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GraphLayout")
	FString LayoutName;
	
	UFUNCTION(BlueprintCallable, Category = "GraphLayout")
	virtual TArray<FVector> GeneratePoints(int32 NumNodes, float Offset);

	UFUNCTION(BlueprintCallable, Category = "GraphLayout")
	virtual TArray<FVector2D> ProjectAllPointsTo2D(const TArray<FVector> Points3D, FVector2D CanvasOrigin);
	
	UFUNCTION(BlueprintCallable, Category = "GraphLayout")
	virtual FVector2D ProjectTo2D(const FVector& Point3D, FVector2D CanvasOrigin);
};
