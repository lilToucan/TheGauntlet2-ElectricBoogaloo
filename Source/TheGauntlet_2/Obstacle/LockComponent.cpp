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
	for (UActorComponent* InteractComponent : GetOwner()->GetComponentsByInterface(UTriggerable::StaticClass()))
	{
		if (InteractComponent == this)
			continue;
		
		TScriptInterface<ITriggerable> ob = TScriptInterface<ITriggerable>(InteractComponent);
		ob.GetInterface()->bIsObstacleActive = false;
		LockedActorComponents.Add(ob);
	}

	for (AActor* keyActor : KeyActors) // binds every given key to the unlock function
	{

		if (!keyActor)
			continue;
		
		UKeyComponent* key = nullptr;
		
		key = Cast<UKeyComponent>(keyActor->GetComponentByClass(UKeyComponent::StaticClass()));

		if (!IsValid(key))
			continue;

		if (LockedActorComponents.Contains(key)) // if the key is on the object i'm on 
		{
			LockedActorComponents.Remove(key); // remove the key from being locked
			key->bIsObstacleActive = true;
		}

		key->OnKeyPickup.AddUObject(this, &ULockComponent::Unlock);
		key->OnReset.AddUObject(this, &ULockComponent::Reset);
		LockCounter++;
	}
}

void ULockComponent::Trigger(){}

void ULockComponent::Reset()
{
	LocksUnlocked--;
	for (TScriptInterface<ITriggerable> Component : LockedActorComponents)
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

	for (TScriptInterface<ITriggerable> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = true;
	}
}


