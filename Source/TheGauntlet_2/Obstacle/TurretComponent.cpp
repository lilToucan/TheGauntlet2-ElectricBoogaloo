#include "TurretComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheGauntlet_2/ObjectPooling/Interfaces/ProjectilePoolable.h"
#include "TheGauntlet_2/PlayerCharacter/GauntletCharacter.h"

// Default Functions:
UTurretComponent::UTurretComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTurretComponent::BeginPlay()
{
	Super::BeginPlay();
	Reset();
}

void UTurretComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bIsObstacleActive)
		return;
	
	if (!Target)
	{
		Target = SearchTarget();;
		return;
	}
	
	if (FVector::Distance(Target->GetActorLocation(),GetOwner()->GetActorLocation()) > SearchRadius)
	{
		Target = nullptr;
		return;
	}
	
	RotationDir = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), Target->GetActorLocation());
	GetOwner()->SetActorRotation(RotationDir);
}

// custom functions:
TSubclassOf<AActor> UTurretComponent::GetBulletClass()
{
	int randomBullet = FMath::RandRange(0, ProjectileUsed.Num()-1);

	if (randomBullet < ProjectileUsed.Num())
		return ProjectileUsed[randomBullet];

	return nullptr;
}

AActor* UTurretComponent::SearchTarget()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	
	TArray<AActor*> ignoreActors;
	ignoreActors.Init(GetOwner(), 1);
	
	FVector sphereSpawnLocation = GetOwner()->GetActorLocation();

	UClass* seekClass = nullptr;

	TArray<AActor*> outActors;
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereSpawnLocation, SearchRadius, traceObjectTypes, seekClass, ignoreActors, outActors);

	AActor* target = nullptr;
	
	for (auto actor : outActors)
	{
		if (actor->IsA(AGauntletCharacter::StaticClass()))
			target = actor; 
	}
	
	return target;
}

void UTurretComponent::FireFunction()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	
	TimerHandle = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTurretComponent::FireFunction, FireRate);

	if (!IsValid(PoolSubsystem) || !bIsObstacleActive || !IsValid(Target))
		return;
	TSubclassOf<AActor> BulletClass = GetBulletClass();
	TScriptInterface<IProjectilePoolable> Bullet = PoolSubsystem->GetActor(BulletClass);

	IProjectilePoolable::Execute_BP_Activate(Bullet.GetObject());

	FTransform spawnTransform = FTransform();
	spawnTransform.SetLocation(GetOwner()->GetActorLocation());
	spawnTransform.SetRotation(GetOwner()->GetActorRotation().Quaternion());
	spawnTransform.SetScale3D(FVector(1, 1, 1));
	IProjectilePoolable::Execute_BP_UpdateTransform(Bullet.GetObject(),spawnTransform,false);
}

void UTurretComponent::Trigger()
{
}

void UTurretComponent::Reset()
{
	PoolSubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
	TimerHandle = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTurretComponent::FireFunction, FireRate);
}


