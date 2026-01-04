#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "GauntletPlayerController.generated.h"

UCLASS(Abstract)
class THEGAUNTLET_2_API AGauntletPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	TArray<UInputMappingContext*> inputMappingContexts;
	
	virtual void SetupInputComponent() override;
};
