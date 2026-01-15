// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "GauntletCharacter.generated.h"

UCLASS()
class THEGAUNTLET_2_API AGauntletCharacter : public ACharacter
{
	GENERATED_BODY()
// variables
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OvelapSphere")
	TEnumAsByte<ECollisionChannel> CollisionChannel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OvelapSphere")
	float OverlapSphereRange = 500.f;

	UPROPERTY(BlueprintReadWrite)
	AActor* Artefact;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAroundInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* InteractInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* PauseInputAction;

// functions
public:
	AGauntletCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	// input functions:
	void MoveInputFunction(const FInputActionValue& InputActionValue);
	void AimInputFunction(const FInputActionValue& InputActionValue);
	void InteractInputFunction(const FInputActionValue& InputActionValue);
	void PauseInputFunction(const FInputActionValue& InputActionValue);


protected:
	TArray<AActor*> OverlapSphere() const;
	virtual void BeginPlay() override;

	
};
