#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "Artefact.generated.h"

UCLASS()
class THEGAUNTLET_2_API AArtefact : public AInteractActor
{
	GENERATED_BODY()
// variables
public:

protected:
	bool IsInteractionActive;

// functions
public:
	AArtefact();
	virtual void Interact(AGauntletCharacter* player) override;
protected:
	virtual void BeginPlay() override;
};
