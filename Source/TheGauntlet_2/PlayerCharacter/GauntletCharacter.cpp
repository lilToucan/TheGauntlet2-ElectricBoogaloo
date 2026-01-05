#include "GauntletCharacter.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheGauntlet_2/GameInstances/GauntletGameInstance.h"
#include "TheGauntlet_2/Interactables/Interacable.h"

AGauntletCharacter::AGauntletCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGauntletCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGauntletCharacter::PauseInputFunction(const FInputActionValue& InputActionValue)
{
	Cast<UGauntletGameInstance>(GetGameInstance())->PauseGame();
}

void AGauntletCharacter::MoveInputFunction(const FInputActionValue& InputActionValue)
{
	if (!GetController())
		return;

	FVector2D input = InputActionValue.Get<FVector2D>();

	// add movement to the movement component
	AddMovementInput(GetActorRightVector(), input.X);
	AddMovementInput(GetActorForwardVector(), input.Y);
}

void AGauntletCharacter::AimInputFunction(const FInputActionValue& InputActionValue)
{
	if (!GetController())
		return;

	FVector2D input = InputActionValue.Get<FVector2D>();

	// give mouse position to the Controller's ControlRotation
	AddControllerYawInput(input.X);
	AddControllerPitchInput(-input.Y);
}

void AGauntletCharacter::InteractInputFunction(const FInputActionValue& InputActionValue)
{
	TArray<AActor*> hitActors = OverlapSphere();

	if (hitActors.Num() <= 0)
		return;

	for (auto actor : hitActors)
	// for each character execute it's interact function unlees there are components with it
	{
		if (!actor->Implements<UInteracable>())
			continue;


		TScriptInterface<IInteracable> ActorInteractable = TScriptInterface<IInteracable>(actor);

		if (ActorInteractable == nullptr)
		{
			continue;
		}

		ActorInteractable.GetInterface()->Interact();
	}
}

TArray<AActor*> AGauntletCharacter::OverlapSphere() const
{
	TArray<TEnumAsByte<EObjectTypeQuery>> EObjectTypeQueryArray;
	EObjectTypeQueryArray.Add(UEngineTypes::ConvertToObjectType(CollisionChannel));
	UClass* actorTypeFilters = nullptr;
	TArray<AActor*> ignoreActors;
	TArray<AActor*> outActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), OverlapSphereRange, EObjectTypeQueryArray,
	                                          actorTypeFilters, ignoreActors, outActors);

	return outActors;
}

void AGauntletCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// aim input
		enhancedInput->BindAction(LookAroundInputAction, ETriggerEvent::Triggered, this,
		                          &AGauntletCharacter::AimInputFunction);

		// interact input :|
		enhancedInput->BindAction(InteractInputAction, ETriggerEvent::Started, this,
		                          &AGauntletCharacter::InteractInputFunction);

		// move inputs :)
		enhancedInput->BindAction(MoveInputAction, ETriggerEvent::Triggered, this,
		                          &AGauntletCharacter::MoveInputFunction);
		enhancedInput->BindAction(MoveInputAction, ETriggerEvent::Completed, this,
		                          &AGauntletCharacter::MoveInputFunction);

		// pasuse input :!
		enhancedInput->BindAction(PauseInputAction, ETriggerEvent::Triggered, this,
		                          &AGauntletCharacter::PauseInputFunction);
	}
}
