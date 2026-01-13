#include "AttachToTargetComponent.h"

#include "GameFramework/Character.h"

UAttachToTargetComponent::UAttachToTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttachToTargetComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttachToTargetComponent::Trigger()
{
	if (Target == nullptr || !bIsObstacleActive)
		return;

	FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	GetOwner()->AttachToActor(Target, rules, SocketName);
	bIsObstacleActive = false;
}

void UAttachToTargetComponent::Reset()
{
	FDetachmentTransformRules rules = FDetachmentTransformRules::KeepWorldTransform;
	GetOwner()->DetachFromActor(rules);
	bIsObstacleActive = true;
}
