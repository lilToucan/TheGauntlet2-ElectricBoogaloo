// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Components/ActorComponent.h"
#include "AutomatickLockComponent.generated.h"


class UKeyComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UAutomatickLockComponent : public UActorComponent, public ITriggerable
{
	GENERATED_BODY()
	

public:	// variables
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> KeyActors;
	
protected: // variables

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TScriptInterface<ITriggerable>> LockedActorComponents;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<UKeyComponent*> KeyComponents;

	int LockCounter = 0;
	int LocksLocked;

	
public:	// functions
	UAutomatickLockComponent();
	virtual void Trigger() override;
	virtual void Reset() override;

protected: // functions
	virtual void Lock();
	virtual void BeginPlay() override;
};
