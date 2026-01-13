#include "FlickLightComponent.h"

UFlickLightComponent::UFlickLightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFlickLightComponent::BeginPlay()
{
	Super::BeginPlay();
	ChangeMaterial();
}

void UFlickLightComponent::ChangeMaterial()
{
	if (!Mesh)
		return;
	
	if (bIsObstacleActive)
		Mesh->SetMaterial(0,UnlockedMaterial);
	else
		Mesh->SetMaterial(0,LockedMaterial);
}

void UFlickLightComponent::Trigger() 
{
	ChangeMaterial();
}

void UFlickLightComponent::Reset() 
{
	ChangeMaterial();
}


