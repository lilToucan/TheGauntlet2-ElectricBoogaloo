// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectilePoolable.generated.h"

UINTERFACE()
class UProjectilePoolable : public UInterface
{
	GENERATED_BODY()
};

class THEGAUNTLET_2_API IProjectilePoolable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(ForceAsFunction), Category="Object Pool Subsystem")
	void BP_Activate();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(ForceAsFunction), Category="Object Pool Subsystem")
	void BP_Deactivate();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(ForceAsFunction), Category ="Object Pool Subsystem")
	void BP_UpdateTransform(FTransform GivenTransform, bool IsSweep = true);
	
};
