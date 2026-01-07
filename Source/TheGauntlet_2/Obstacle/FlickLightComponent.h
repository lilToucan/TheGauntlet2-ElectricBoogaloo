#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Components/ActorComponent.h"
#include "FlickLightComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UFlickLightComponent : public UActorComponent, public ITriggerable
{
	GENERATED_BODY()

// variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|FlickLight")
	UStaticMeshComponent* Mesh;
	UPROPERTY()
	UMaterialInterface* BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|FlickLight")
	UMaterialInterface* LockedMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|FlickLight")
	UMaterialInterface* UnlockedMaterial;

protected:

// functions
public:
	UFlickLightComponent();
	virtual void Trigger() override;
	virtual void Reset() override;

protected:
	virtual void BeginPlay() override;
	virtual void ChangeMaterial();
};
