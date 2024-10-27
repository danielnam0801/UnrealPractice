// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/FVGameInteface.h"
#include "FVGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API AFVGameModeBase : public AGameModeBase, public IFVGameInteface
{
	GENERATED_BODY()

public:
	AFVGameModeBase();
public:
	virtual void OnGameStart() override;
	virtual void OnPlayerScoreChanged(int32 NewPlayerScore) override;
	virtual void OnPlayerDead() override;
	virtual bool IsGameCleared() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game, Meta = (AllowPrivateAccess = "true"))
	int32 ClearScore;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentScore;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game, Meta = (AllowPrivateAccess = "true"))
	uint8 bIsCleared : 1;
};
