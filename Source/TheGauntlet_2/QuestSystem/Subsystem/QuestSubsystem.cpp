#include "QuestSubsystem.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

FQuestDataStruct& UQuestSubsystem::GetCurrentQuest()
{
		return *AllQuests[0];
}

void UQuestSubsystem::OnStreamableComplete()
{
	// play the sound
	USoundBase* LoadedSound = CurrentQuest.SoundEffect.Get();
	if (!LoadedSound)
		return;
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Log, TEXT("1289"));
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), LoadedSound);
}

void UQuestSubsystem::QuestComplete()
{
	CurrentQuest = GetCurrentQuest();
	if (CurrentQuest.SoundEffect->GetPathName() == "")
		return;

	// load asset 
	FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
	SFXHandle = StreamableManager.RequestAsyncLoad(
		CurrentQuest.SoundEffect.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &UQuestSubsystem::OnStreamableComplete), 0, false);
	OnQuestComplete.Broadcast();
}

void UQuestSubsystem::ReceiveQuests(FDataTableRowHandle QuestDataTable)
{
	QuestDataTableRow = &QuestDataTable;
	QuestDataTableRow->DataTable->GetAllRows("",AllQuests);
}
