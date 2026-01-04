// Fill out your copyright notice in the Description page of Project Settings.


#include "LockedComponent.h"

#include "KeyComponent.h"

ULockedComponent::ULockedComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULockedComponent::BeginPlay()
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

		key->OnUnlock.AddUObject(this, &ULockedComponent::Unlock);
		key->OnReset.AddUObject(this, &ULockedComponent::Reset);
		LockCounter++;
	}
}

void ULockedComponent::Trigger(){}

void ULockedComponent::Reset()
{
	LocksUnlocked--;
	for (TScriptInterface<IObstacle> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = false;
		Component.GetInterface()->Reset();
	}
}

void ULockedComponent::Unlock()
{
	LocksUnlocked++;
	if (LocksUnlocked < LockCounter)
		return;

	//GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "Unlocked");
	for (TScriptInterface<IObstacle> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = true;
	}
}


