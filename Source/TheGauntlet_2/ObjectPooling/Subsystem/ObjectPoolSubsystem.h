#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TheGauntlet_2/Structs/FObjectPool.h"
#include "TheGauntlet_2/ObjectPooling/Interfaces/ProjectilePoolable.h"
#include "ObjectPoolSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInactiveObjectsChange, TSubclassOf<AActor>, ActorClass,float ,NumInactiveObjects);

UCLASS()
class THEGAUNTLET_2_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintType,BlueprintAssignable,BlueprintReadWrite, Category="Object Pool Subsystem")
	FInactiveObjectsChange OnInactivePoolingObjectsChanged;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Object Pool Subsystem")
	TMap<TSubclassOf<AActor>,FObjectPool> ObjectPoolMap;


	UFUNCTION(BlueprintCallable, Category = "Object Pool Subsystem")
	void AddPool(TSubclassOf<AActor> ActorClass, int32 initialSize = 50);

	UFUNCTION(BlueprintCallable, Category = "Object Pool Subsystem")
	TScriptInterface<IProjectilePoolable> GetActor(TSubclassOf<AActor> ActorClass);
	UFUNCTION(BlueprintCallable, Category = "Object Pool Subsystem")
	void ReturnActorToPool(TSubclassOf<AActor> ActorClass, TScriptInterface<IProjectilePoolable> actorToReturn);

};
