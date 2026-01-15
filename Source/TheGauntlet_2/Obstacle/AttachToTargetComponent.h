#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Components/ActorComponent.h"
#include "AttachToTargetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UAttachToTargetComponent : public UActorComponent, public ITriggerable
{
	GENERATED_BODY()
// variables
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName SocketName;
protected:

// functions
public:
	UAttachToTargetComponent();
	virtual void Trigger() override;
	virtual void Reset() override;

protected:
	virtual void BeginPlay() override;
};
