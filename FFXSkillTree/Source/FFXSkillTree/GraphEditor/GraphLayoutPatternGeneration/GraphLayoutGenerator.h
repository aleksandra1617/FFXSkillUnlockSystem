#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "GraphLayoutGenerator.generated.h"

class UNodePattern;
/**
 * 
 */
UCLASS()
class FFXSKILLTREE_API UGraphLayoutGenerator : public UEditorSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Graph Layout")
	UNodePattern* GeneratePattern(TSubclassOf<UGraphLayoutStrategyBase> StrategyClass, int32 NumNodes, float Offset);

	// Should add a pattern validation function later to ensure the pattern is never generated out of bounds. 
};
