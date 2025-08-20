#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NodePattern.generated.h"

/**
 * 
 */
UCLASS()
class FFXSKILLTREE_API UNodePattern : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node Pattern")
	TArray<FVector> Points3D;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node Pattern")
	TArray<FVector2D> ProjectedPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node Pattern")
	FString PatternName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node Pattern")
	int32 NodeCount;
};
