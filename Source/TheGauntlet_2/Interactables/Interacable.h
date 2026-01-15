#pragma once

#include "CoreMinimal.h"
#include "TheGauntlet_2/PlayerCharacter/GauntletCharacter.h"
#include "UObject/Interface.h"
#include "Interacable.generated.h"

UINTERFACE(MinimalAPI)
class UInteracable : public UInterface
{
	GENERATED_BODY()
};

class THEGAUNTLET_2_API IInteracable
{
	GENERATED_BODY()
	
public:
	virtual void Interact(AGauntletCharacter*) = 0;
};
