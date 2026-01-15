#pragma once
#include "FQuestDataStruct.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FQuestDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FString QuestHudName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSoftObjectPtr<USoundBase> SoundEffect;
};
