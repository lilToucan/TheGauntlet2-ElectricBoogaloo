#include "Artefact.h"

AArtefact::AArtefact()
{
	PrimaryActorTick.bCanEverTick = false;
	IsInteractionActive = true;
}

void AArtefact::BeginPlay()
{
	Super::BeginPlay();
}

void AArtefact::Interact(AGauntletCharacter* player)
{
	if (!IsInteractionActive)
		return;
	
	for (auto interactableComp : interactableComponents)
	{
		interactableComp.GetInterface()->Trigger();
		interactableComp->bIsObstacleActive = false;
	}
	IsInteractionActive = false;
	player->Artefact = this;
	SetActorEnableCollision(false);
}


