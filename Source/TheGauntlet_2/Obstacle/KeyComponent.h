#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Components/ActorComponent.h"

#include "KeyComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UKeyComponent : public UActorComponent, public IObstacle
{
	GENERATED_BODY()

// variables
public: 
	FDelegate OnUnlock;
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
