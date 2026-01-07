#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Triggerable.generated.h"
UINTERFACE()
// only used on ActorComponents or SceneComponents
class UTriggerable : public UInterface 
{
	GENERATED_BODY()
};

class THEGAUNTLET_2_API ITriggerable
{
	GENERATED_BODY()
public:
	virtual void Trigger() = 0;
	virtual void Reset() = 0;
	// whether the obstacle is active or not
	bool bIsObstacleActive = true;
};
