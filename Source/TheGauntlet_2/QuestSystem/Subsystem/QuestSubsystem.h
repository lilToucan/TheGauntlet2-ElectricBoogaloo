#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TheGauntlet_2/QuestSystem/DataTableStruct/FQuestDataStruct.h"
#include "QuestSubsystem.generated.h"

struct FStreamableHandle;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestCompleteDelegate);

UCLASS()
class THEGAUNTLET_2_API UQuestSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnQuestCompleteDelegate OnQuestComplete;
protected:
	FDataTableRowHandle* QuestDataTableRow;
	int QuestIndex = 0;
	FQuestDataStruct CurrentQuest;
	TSharedPtr<FStreamableHandle> SFXHandle;
	TArray<FQuestDataStruct*> AllQuests;

public:
	UFUNCTION(BlueprintCallable)
	FQuestDataStruct& GetCurrentQuest();
	void OnStreamableComplete();
	UFUNCTION(BlueprintCallable)
	void QuestComplete();

	UFUNCTION(BlueprintCallable)
	void ReceiveQuests(FDataTableRowHandle QuestDataTable);
};
