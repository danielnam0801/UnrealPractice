// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FVHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API UFVHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFVHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UFVHpBarWidget> HpBar;
};
