#include "AttachToTargetComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

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
	if (!bIsObstacleActive)
		return;

	FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetIncludingScale;
	AActor* Target = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	if (!Target)
		return;
	USkeletalMeshComponent* MeshComp = Target->FindComponentByClass<USkeletalMeshComponent>();
	if (!MeshComp)
		return;
	
	GetOwner()->AttachToComponent(MeshComp, rules, SocketName);
	bIsObstacleActive = false;
}

void UAttachToTargetComponent::Reset()
{
	FDetachmentTransformRules rules = FDetachmentTransformRules::KeepWorldTransform;
	GetOwner()->DetachFromActor(rules);
	bIsObstacleActive = true;
}
