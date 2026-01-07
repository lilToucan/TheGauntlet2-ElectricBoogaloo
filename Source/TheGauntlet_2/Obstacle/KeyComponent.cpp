#include "KeyComponent.h"

UKeyComponent::UKeyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKeyComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKeyComponent::Trigger()
{
	if (!bIsObstacleActive)
		return;

	if (bIsTimed)
		GetOwner()->GetWorldTimerManager().SetTimer(DelayedReset, this, &UKeyComponent::Reset, Duration);
	
	OnKeyPickup.Broadcast();
	bIsObstacleActive = false;
}

void UKeyComponent::Reset()
{
	OnReset.Broadcast();
	bIsObstacleActive = true;
	GetOwner()->GetWorldTimerManager().ClearTimer(DelayedReset);
}


