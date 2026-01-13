#include "OneTimeUseInteractable.h"

AOneTimeUseInteractable::AOneTimeUseInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	IsInteractionActive = true;
}

void AOneTimeUseInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AOneTimeUseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOneTimeUseInteractable::Interact()
{
	if (!IsInteractionActive)
		return;
	
	for (auto interactableComp : interactableComponents)
	{
		interactableComp.GetInterface()->Trigger();
		interactableComp->bIsObstacleActive = false;
	}
	IsInteractionActive = false;
}


