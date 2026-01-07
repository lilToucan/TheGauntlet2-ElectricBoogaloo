#include "AutomatickLockComponent.h"

#include "KeyComponent.h"

UAutomatickLockComponent::UAutomatickLockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAutomatickLockComponent::BeginPlay()
{
	Super::BeginPlay();
	LockedActorComponents.Empty();
	for (UActorComponent* InteractComponent : GetOwner()->GetComponentsByInterface(UTriggerable::StaticClass()))
	{
		if (InteractComponent == this) // TODO: CHECK IF THIS EVER BECOMES TRUE :) 
			continue;
		
		TScriptInterface<ITriggerable> ob = TScriptInterface<ITriggerable>(InteractComponent);
		LockedActorComponents.Add(ob);
	}
	
	for (AActor* keyActor : KeyActors) // binds every given key to the unlock function
	{
		UKeyComponent* key = Cast<UKeyComponent>(keyActor->GetComponentByClass(UKeyComponent::StaticClass()));

		if (!IsValid(key))
			continue;

		key->OnKeyPickup.AddUObject(this, &UAutomatickLockComponent::Lock);
		key->OnReset.AddUObject(this, &UAutomatickLockComponent::Reset);
		LockCounter++;
	}
}
void UAutomatickLockComponent::Trigger(){}

void UAutomatickLockComponent::Reset() // basically unlock
{
	LocksLocked--;

	for (TScriptInterface<ITriggerable> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = true;
		Component.GetInterface()->Trigger();
	}
}

void UAutomatickLockComponent::Lock()
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


