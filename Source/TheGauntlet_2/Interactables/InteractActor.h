#pragma once

#include "CoreMinimal.h"
#include "Interacable.h"
#include "GameFramework/Actor.h"
#include "TheGauntlet_2/Obstacle/Triggerable.h"

#include "InteractActor.generated.h"

UCLASS()
class THEGAUNTLET_2_API AInteractActor : public AActor, public IInteracable
{
	GENERATED_BODY()

public:
	TArray<TScriptInterface<ITriggerable>> interactableComponents;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	AInteractActor();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
};
