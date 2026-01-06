#pragma once

#include "CoreMinimal.h"
#include "LockComponent.h"
#include "AutomaticUnlockComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_2_API UAutomaticUnlockComponent : public ULockComponent
{
	GENERATED_BODY()
// variables
public:

protected:

// functions
public:
	UAutomaticUnlockComponent();
	virtual void Trigger() override;
	virtual void Reset() override;

protected:
	virtual void BeginPlay() override;
	virtual void Unlock() override;
	
};
