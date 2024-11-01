// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FVPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API AFVPlayerController : public APlayerController
{
	GENERATED_BODY()

public:	
	AFVPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnScoreChangedCpp"))
	void OnScoreChanged(int32 NewScore);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnGameClearCpp"))
	void OnGameClear();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnGameOverCpp"))
	void OnGameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnGameRetryCountCpp"))
	void OnGameRetryCount(int32 NewRetryCount);

	void GameStart();
	void GameScoreChanged(int32 NewScore);
	void GameClear();
	void GameOver();

	// HUD Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UFVHUDWidget> FVHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UFVHUDWidget> FVHUDWidget;
//
//	// Save Game Section
//protected:
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
//	TObjectPtr<class UABSaveGame> SaveGameInstance;
	
	
public:
	bool canControl = false;

};
