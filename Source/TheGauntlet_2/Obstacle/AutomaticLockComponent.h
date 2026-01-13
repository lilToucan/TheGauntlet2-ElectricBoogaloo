// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Components/ActorComponent.h"
#include "AutomaticLockComponent.generated.h"


class UKeyComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UAutomaticLockComponent : public UActorComponent, public ITriggerable
{
	GENERATED_BODY()
	

public:	// variables
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> KeyActors;
	
protected: // variables

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TScriptInterface<ITriggerable>> LockedActorComponents;


	int LockCounter = 0;
	int LocksLocked;

	
public:	// functions
	UAutomaticLockComponent();
	virtual void Trigger() override;
	virtual void Reset() override;

protected: // functions
	virtual void Lock();
	virtual void BeginPlay() override;
};
