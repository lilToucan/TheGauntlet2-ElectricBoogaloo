#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Obstacle.generated.h"
UINTERFACE()
class UObstacle : public UInterface
{
	GENERATED_BODY()
};

class THEGAUNTLET_2_API IObstacle
{
	GENERATED_BODY()
public:
	virtual void Trigger() = 0;
	virtual void Reset() = 0;
	// whether the obstacle is active or not
	bool bIsObstacleActive = true;
};
