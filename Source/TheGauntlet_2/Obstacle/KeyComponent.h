#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Components/ActorComponent.h"

#include "KeyComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UKeyComponent : public UActorComponent, public ITriggerable
{
	GENERATED_BODY()

// variables
public: 
	FDelegate OnKeyPickup;
	FDelegate OnReset;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Key Component")
	bool bIsTimed;
	UPROPERTY(EditAnywhere, Category = "Key Component")
	float Duration = 5.f;
	FTimerHandle DelayedReset;

//functions
public: 
	UKeyComponent();
	virtual void Trigger() override;
	virtual void Reset() override;

protected:
	virtual void BeginPlay() override;
};
