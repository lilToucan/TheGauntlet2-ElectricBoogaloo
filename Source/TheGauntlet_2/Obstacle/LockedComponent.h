// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyComponent.h"
#include "Obstacle.h"
#include "Components/ActorComponent.h"
#include "LockedComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API ULockedComponent : public UActorComponent, public IObstacle
{
	GENERATED_BODY()

public:	// variables
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> KeyActors;
	
protected: // variables

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TScriptInterface<IObstacle>> LockedActorComponents;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<UKeyComponent*> KeyComponents;

	int LockCounter = 0;
	int LocksUnlocked;

	
public:	// functions
	ULockedComponent();
	virtual void Trigger() override;
	virtual void Reset() override;

protected: // functions
	void Unlock();
	virtual void BeginPlay() override;
};
