
#include "ObjectPoolSubsystem.h"

void UObjectPoolSubsystem::AddPool(TSubclassOf<AActor> ActorClass, int32 initialSize)
{
	if (!GetWorld() || !ActorClass->ImplementsInterface(UProjectilePoolable::StaticClass()))
		return;

	FObjectPool NewPool = FObjectPool();
	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();

	for (int i = 0; i < initialSize; i++)
	{
		// spawn and add it to the pool
		AActor* newActor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnParameters); 
		IProjectilePoolable::Execute_BP_Deactivate(newActor);
		NewPool.InactivePoolingObjects.AddUnique(TScriptInterface<IProjectilePoolable>(newActor));
	}

	if (ObjectPoolMap.Contains(ActorClass))
	{
		ObjectPoolMap[ActorClass].InactivePoolingObjects.Append(NewPool.InactivePoolingObjects);
		OnInactivePoolingObjectsChanged.Broadcast(ActorClass, NewPool.InactivePoolingObjects.Num());
		return;
	}

	ObjectPoolMap.Add(ActorClass, NewPool);
	OnInactivePoolingObjectsChanged.Broadcast(ActorClass, NewPool.InactivePoolingObjects.Num());
}

TScriptInterface<IProjectilePoolable> UObjectPoolSubsystem::GetActor(TSubclassOf<AActor> ActorClass)
{
	if (!GetWorld() || !ActorClass->ImplementsInterface(UProjectilePoolable::StaticClass()))
		return nullptr;

	if (!ObjectPoolMap.Contains(ActorClass))
	{
		AddPool(ActorClass);
	}
	FObjectPool* PoolObject = ObjectPoolMap.Find(ActorClass);

	if (PoolObject->InactivePoolingObjects.IsEmpty())
		AddPool(ActorClass, 10);

	TScriptInterface<IProjectilePoolable> result = PoolObject->InactivePoolingObjects[0];

	if (result.GetInterface() == nullptr)
		IProjectilePoolable::Execute_BP_Activate(result.GetObject());
	else
		result.GetInterface()->BP_Activate_Implementation();

	PoolObject->InactivePoolingObjects.Remove(result);
	PoolObject->ActivePoolingObjects.AddUnique(TScriptInterface<IProjectilePoolable>(result));
	OnInactivePoolingObjectsChanged.Broadcast(ActorClass, PoolObject->InactivePoolingObjects.Num());
	return result;
}

void UObjectPoolSubsystem::ReturnActorToPool(TSubclassOf<AActor> ActorClass,TScriptInterface<IProjectilePoolable> actorToReturn)
{
	if (!ObjectPoolMap.Contains(ActorClass) || !GetWorld() || !ActorClass->ImplementsInterface(
		UProjectilePoolable::StaticClass()))
		return;

	FObjectPool* PoolObject = ObjectPoolMap.Find(ActorClass);

	if (!PoolObject->ActivePoolingObjects.Contains(actorToReturn))
		return;

	PoolObject->ActivePoolingObjects.Remove(actorToReturn);
	PoolObject->InactivePoolingObjects.AddUnique(TScriptInterface<IProjectilePoolable>(actorToReturn));
	OnInactivePoolingObjectsChanged.Broadcast(ActorClass, PoolObject->InactivePoolingObjects.Num());
}