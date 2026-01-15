#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "Altar.generated.h"

UCLASS()
class THEGAUNTLET_2_API AAltar : public AInteractActor
{
	GENERATED_BODY()

// variables
public:

protected:

	bool IsInteractionActive = true;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="helloworld", meta = (AllowPrivateAccess = "true")) 
	class UStaticMeshComponent* MeshComponent;
	
// functions
public:
	AAltar();
	virtual void Interact(AGauntletCharacter* player) override;
protected:
	virtual void BeginPlay() override;
};
