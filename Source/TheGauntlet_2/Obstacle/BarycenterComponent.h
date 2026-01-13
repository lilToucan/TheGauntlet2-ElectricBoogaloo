#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Components/ActorComponent.h"
#include "BarycenterComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UBarycenterComponent : public UActorComponent, public ITriggerable
{
	GENERATED_BODY()
// variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="BarycenterComponent|Settings")
	TArray<AActor*> Satellites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="BarycenterComponent|Settings")
	FVector OffsetPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="BarycenterComponent|Settings")
	FRotator OffsetRot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="BarycenterComponent|Settings")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="BarycenterComponent|Settings")
	bool bOrbitCounterClockWise;

protected:
	float Timer = 0;

// functions
public:
	UBarycenterComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Trigger() override;
	virtual void Reset() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void Rotate(AActor* Satellite, float DistanceOffset );
};
