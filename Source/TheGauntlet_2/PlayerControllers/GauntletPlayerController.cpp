#include "GauntletPlayerController.h"

#include "EnhancedInputSubsystems.h"

void AGauntletPlayerController::SetupInputComponent()
{
	if (!IsLocalPlayerController())
		return;

	UEnhancedInputLocalPlayerSubsystem* enhancedSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!enhancedSubSystem)
		return;

	for (UInputMappingContext* mappingContext : inputMappingContexts)
	{
		enhancedSubSystem->AddMappingContext(mappingContext,0);
	}
}
