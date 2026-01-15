#include "MoveComponent.h"

#include "Kismet/KismetStringLibrary.h"

UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	bIsObstacleActive = false;
	ActorOwner = GetOwner();
	beginLocation = ActorOwner->GetActorLocation();
	startLocation = ActorOwner->GetActorLocation();
	currentWaypoint = 1;

	if (Waypoints.Num() < 1) // basically if there are no waypoints set up stand still 
		currentWaypoint = 0;
	

	endLocation = Waypoints[currentWaypoint].WayPoint + beginLocation;
	duration = Waypoints[currentWaypoint].duration;
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsObstacleActive && !bIsResetting)
		return;

	timer += DeltaTime;
	if (timer > duration) // if the timer is over reset timer and get the next waypoint
	{
		if (bIsResetting)
			bIsResetting = false;

		currentWaypoint++;

		// if the waypoint index has surpassed the last then set it back to the first 
		if (currentWaypoint >= Waypoints.Num())
		{
			if (!bIsPingPong)
			{
				bIsObstacleActive = false;
				return;
			}
			currentWaypoint = 0;
		}

		timer = 0.f;
		startLocation = ActorOwner->GetActorLocation();
		endLocation = Waypoints[currentWaypoint].WayPoint + beginLocation;
		duration = Waypoints[currentWaypoint].duration;
	}
	FVector newLocation = FMath::Lerp(startLocation, endLocation, timer / duration);

	ActorOwner->SetActorLocation(newLocation);
}

void UMoveComponent::Trigger()
{
}

void UMoveComponent::Reset()
{
	timer = 0.f;
	currentWaypoint = 0;
	startLocation = ActorOwner->GetActorLocation();
	endLocation = Waypoints[currentWaypoint].WayPoint + beginLocation;
	duration = Waypoints[currentWaypoint].duration;
	bIsResetting = true;
}
