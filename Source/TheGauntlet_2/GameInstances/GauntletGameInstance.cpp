#include "GauntletGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UGauntletGameInstance::LoadLevel(TSoftObjectPtr<UWorld> NewLevel)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),NewLevel);
}

void UGauntletGameInstance::Quit()
{
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	UKismetSystemLibrary::QuitGame(GetWorld(),GetPrimaryPlayerController(),QuitPreference,false);
}

void UGauntletGameInstance::ResumeGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),1);
}

void UGauntletGameInstance::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0);
}