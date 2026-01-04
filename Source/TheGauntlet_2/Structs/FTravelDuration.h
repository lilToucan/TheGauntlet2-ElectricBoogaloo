#pragma once

#include "FTravelDuration.generated.h"

USTRUCT(BlueprintType)
struct FTravelDuration
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,meta=(MakeEditWidget = true))
	FVector WayPoint;
	UPROPERTY(EditAnywhere,meta=(ClampMin=0.1f))
	float duration = 0.1f;
};
