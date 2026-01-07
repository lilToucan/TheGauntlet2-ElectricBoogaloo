#include "AutomaticUnlockComponent.h"

UAutomaticUnlockComponent::UAutomaticUnlockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAutomaticUnlockComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAutomaticUnlockComponent::Trigger(){}

void UAutomaticUnlockComponent::Reset()
{
	Super::Reset();
}

void UAutomaticUnlockComponent::Unlock()
{
	LocksUnlocked++;
	if (LocksUnlocked < LockCounter)
		return;

	for (TScriptInterface<ITriggerable> Component : LockedActorComponents)
	{
		Component.GetInterface()->bIsObstacleActive = true;
		Component.GetInterface()->Trigger();
	}
}

