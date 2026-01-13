#include "BarycenterComponent.h"

#include "Kismet/KismetMathLibrary.h"

UBarycenterComponent::UBarycenterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsObstacleActive = false;
}

void UBarycenterComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBarycenterComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (Satellites.Num() == 0 || !bIsObstacleActive)
		return;

	Timer += DeltaTime * RotationSpeed;
	int i = 0;

	for (AActor* Satellite : Satellites)
	{
		if (!Satellite)
			continue;
		i++;
		Rotate(Satellite, ((2 * PI)/ Satellites.Num())*i);
	}
}

void UBarycenterComponent::Rotate(AActor* Satellite, const float DistanceOffset)
{
	//Desmos made me se infinity
	float x = -FMath::Cos(Timer + DistanceOffset) * OffsetPos.X;
	float y = (FMath::Sin(Timer + DistanceOffset)) * OffsetPos.Y;

	FRotator OrbitRotation = GetOwner()->GetActorRotation() + OffsetRot;

	if (bOrbitCounterClockWise)
		x *= -1;
	FVector OrbitPos = (OrbitRotation.Quaternion() * FVector(x, y, OffsetPos.Z)) + GetOwner()->GetActorLocation();
	
	Satellite->SetActorLocation(OrbitPos);
	Satellite->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(OrbitPos, GetOwner()->GetActorLocation()));
}


void UBarycenterComponent::Trigger()
{
	if (bIsObstacleActive == false)
		return;

	bIsObstacleActive = true;
}


void UBarycenterComponent::Reset()
{
	bIsObstacleActive = false;
}


