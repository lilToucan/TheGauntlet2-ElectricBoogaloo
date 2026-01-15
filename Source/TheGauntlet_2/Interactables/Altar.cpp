#include "Altar.h"

#include "TheGauntlet_2/QuestSystem/Subsystem/QuestSubsystem.h"

AAltar::AAltar()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	if (RootComponent)
		MeshComponent->SetupAttachment(RootComponent);
}

void AAltar::BeginPlay()
{
	Super::BeginPlay();
}

void AAltar::Interact(AGauntletCharacter* player)
{
	if (!player->Artefact || !IsInteractionActive)
		return;

	player->Artefact->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, "Top");
	Super::Interact(player);
	GetWorld()->GetSubsystem<UQuestSubsystem>()->QuestComplete();
	IsInteractionActive = false;
}
