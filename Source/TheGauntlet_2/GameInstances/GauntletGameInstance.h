#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GauntletGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameTimeDialationChangeDelegate);

UCLASS(Abstract)
class THEGAUNTLET_2_API UGauntletGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bIsPaused = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, BlueprintAssignable,BlueprintCallable)
	FOnGameTimeDialationChangeDelegate OnGameTimeDialationChange;
	UFUNCTION(BlueprintCallable, Category ="LoadLevel")
	void LoadLevel(TSoftObjectPtr<UWorld> NewLevel);
	UFUNCTION(BlueprintCallable, Category = "InGameMenu")
	void Quit();
	UFUNCTION(BlueprintCallable, Category = "InGameMenu")
	void ResumeGame();
	UFUNCTION(BlueprintCallable, Category = "InGameMenu")
	void PauseGame();
};
