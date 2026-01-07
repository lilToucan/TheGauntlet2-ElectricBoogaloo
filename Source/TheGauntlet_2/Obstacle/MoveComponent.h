// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Components/SceneComponent.h"
#include "TheGauntlet_2/Structs/FTravelDuration.h"
#include "MoveComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UMoveComponent : public USceneComponent, public ITriggerable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = true), Category="Settings")
	TArray<FTravelDuration> Waypoints;

	UMoveComponent();

protected:
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bIsPingPong = true;
	UPROPERTY()
	AActor* ActorOwner;
	FVector beginLocation;
	FVector startLocation;
	FVector endLocation;
	float timer = 0.f;
	float duration = 0.1f;
	int currentWaypoint = 0;
	bool bIsResetting = false;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Trigger() override;
	virtual void Reset() override;

protected:
	virtual void BeginPlay() override;
};
