#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Components/ActorComponent.h"
#include "TheGauntlet_2/ObjectPooling/Subsystem/ObjectPoolSubsystem.h"
#include "TurretComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UTurretComponent : public UActorComponent, public IObstacle
{
	GENERATED_BODY()
// variables 
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (MustImplement = "ProjectilePoolable"),Category="Spawning")
	TArray<TSubclassOf<AActor>> ProjectileUsed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawning")
	float FireRate = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawning")
	float SearchRadius = 300;
protected:
	UPROPERTY()
	UObjectPoolSubsystem* PoolSubsystem;
	UPROPERTY()
	AActor* Target;
	FTimerHandle TimerHandle;
	FRotator RotationDir;
	
// Functions
public:
	UTurretComponent();
	virtual void FireFunction();
	virtual void Trigger() override;
	virtual void Reset() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;
	virtual TSubclassOf<AActor> GetBulletClass();
	virtual AActor* SearchTarget();
	
};
