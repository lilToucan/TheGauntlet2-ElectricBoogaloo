#include "AutomaticLockComponent.h"

#include "KeyComponent.h"

UAutomaticLockComponent::UAutomaticLockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAutomaticLockComponent::BeginPlay()
{
	Super::BeginPlay();
	LockedActorComponents.Empty();
	for (UActorComponent* InteractComponent : GetOwner()->GetComponentsByInterface(UTriggerable::StaticClass()))
	{
		if (InteractComponent == this) // TODO: CHECK IF THIS EVER BECOMES TRUE :) 
			continue;
		
		TScriptInterface<ITriggerable> Triggerable = TScriptInterface<ITriggerable>(InteractComponent);
		LockedActorComponents.Add(Triggerable);
	}
	
	for (AActor* keyActor : KeyActors) // binds every given key to the unlock function
	{
		if (!keyActor)
			continue;
		
		UKeyComponent* key = Cast<UKeyComponent>(keyActor->GetComponentByClass(UKeyComponent::StaticClass()));

		if (!IsValid(key))
			continue;
		
		if (LockedActorComponents.Contains(key)) // if the key is on the object I'm on 
		{
			LockedActorComponents.Remove(key); // remove the key from being locked
			key->bIsObstacleActive = true; // turn it back on
		}
		
		key->OnKeyPickup.AddUObject(this, &UAutomaticLockComponent::Lock);
		key->OnReset.AddUObject(this, &UAutomaticLockComponent::Reset);
		LockCounter++;
	}
}

void UAutomaticLockComponent::Trigger()
{
}

void UAutomaticLockComponent::Reset() // basically unlock
{
	LocksLocked--;

	for (TScriptInterface<ITriggerable> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = true;
		Component.GetInterface()->Trigger();
	}
}

void UAutomaticLockComponent::Lock()
{
	LocksLocked++;
	if (LocksLocked < LockCounter)
		return;

	for (TScriptInterface<ITriggerable> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = false;
		Component.GetInterface()->Reset();
	}
}
