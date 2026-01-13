#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "OneTimeUseInteractable.generated.h"

UCLASS()
class THEGAUNTLET_2_API AOneTimeUseInteractable : public AInteractActor
{
	GENERATED_BODY()
// variables
public:

protected:
	bool IsInteractionActive;

// functions
public:
	virtual void Tick(float DeltaTime) override;
	AOneTimeUseInteractable();
	virtual void Interact() override;
protected:
	virtual void BeginPlay() override;
};
