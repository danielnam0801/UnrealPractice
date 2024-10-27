// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/FVUserWidget.h"
#include "GameData/FVCharacterStat.h"
#include "FVHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API UFVHpBarWidget : public UFVUserWidget
{
	GENERATED_BODY()

public:
	UFVHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(const FFVCharacterStat& BaseStat, const FFVCharacterStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);

	FString GetHpStatText();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HPProgress)
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HpStat;

	UPROPERTY()
	float MaxHp;

	UPROPERTY()
	float CurrentHp;
};
