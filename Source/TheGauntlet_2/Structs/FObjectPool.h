#pragma once
#include "TheGauntlet_2/ObjectPooling/Interfaces/ObjectPoolable.h"

#include "FObjectPool.generated.h"

USTRUCT(BlueprintType)
struct FObjectPool
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "object to Pool")
	TArray<TScriptInterface<IObjectPoolable>> ActivePoolingObjects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "object to Pool")
	TArray<TScriptInterface<IObjectPoolable>> InactivePoolingObjects;
};
