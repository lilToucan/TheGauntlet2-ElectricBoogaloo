#include "InteractActor.h"

AInteractActor::AInteractActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	int x = GetComponentsByInterface(UObstacle::StaticClass()).Num();
	
	for (UActorComponent* interactComponent : GetComponentsByInterface(UObstacle::StaticClass()))
	{
		TScriptInterface<IObstacle> interactComp = TScriptInterface<IObstacle>(interactComponent);

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

