#include "LockComponent.h"
#include "KeyComponent.h"

ULockComponent::ULockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULockComponent::BeginPlay()
{
	Super::BeginPlay();

	LockedActorComponents.Empty();
	for (UActorComponent* interactComponent : GetOwner()->GetComponentsByInterface(UObstacle::StaticClass()))
	{
		TScriptInterface<IObstacle> ob = TScriptInterface<IObstacle>(interactComponent);
		ob.GetInterface()->bIsObstacleActive = false;
		LockedActorComponents.Add(ob);
	}
	
	if (LockedActorComponents.Contains(this))
	{
		bIsObstacleActive = true;
		LockedActorComponents.Remove(this);
	}

	for (AActor* keyActor : KeyActors) // binds every given key to the unlock function
	{
		UKeyComponent* key = Cast<UKeyComponent>(keyActor->GetComponentByClass(UKeyComponent::StaticClass()));

		if (!IsValid(key))
			continue;

		key->OnUnlock.AddUObject(this, &ULockComponent::Unlock);
		key->OnReset.AddUObject(this, &ULockComponent::Reset);
		LockCounter++;
	}
}

void ULockComponent::Trigger(){}

void ULockComponent::Reset()
{
	LocksUnlocked--;
	for (TScriptInterface<IObstacle> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = false;
		Component.GetInterface()->Reset();
	}
}

void ULockComponent::Unlock()
{
	LocksUnlocked++;
	if (LocksUnlocked < LockCounter)
		return;

	for (TScriptInterface<IObstacle> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = true;
	}
}


