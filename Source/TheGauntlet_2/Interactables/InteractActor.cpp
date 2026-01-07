#include "InteractActor.h"

AInteractActor::AInteractActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	int x = GetComponentsByInterface(UTriggerable::StaticClass()).Num();
	
	for (UActorComponent* interactComponent : GetComponentsByInterface(UTriggerable::StaticClass()))
	{
		TScriptInterface<ITriggerable> interactComp = TScriptInterface<ITriggerable>(interactComponent);

		if (interactComp == nullptr)
			continue;
		interactableComponents.Add(interactComp);
	}
}

void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractActor::Interact()
{
	for (auto interactableComp : interactableComponents)
	{
		interactableComp.GetInterface()->Trigger();
	}
}

