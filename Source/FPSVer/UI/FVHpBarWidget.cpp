// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FVHpBarWidget.h"
#include "Components/ProgressBar.h"
#include <Components/TextBlock.h>
#include "Interface/FVCharacterWidgetInterface.h"

UFVHpBarWidget::UFVHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UFVHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar);

	/*IFVCharacterWidgetInterface* CharacterWidget = Cast<IFVCharacterWidgetInterface>(OwningActor);

	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}*/
}

void UFVHpBarWidget::UpdateStat(const FFVCharacterStat& BaseStat, const FFVCharacterStat& ModifierStat)
{
	MaxHp = (BaseStat + ModifierStat).MaxHp;

	if (HpProgressBar)
	{
		UE_LOG(LogTemp, Log, TEXT("UpdateStat"));
		HpProgressBar->SetPercent(CurrentHp / MaxHp);
	}

	if (HpStat)
	{
		HpStat->SetText(FText::FromString(GetHpStatText()));
	}
}

void UFVHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);

	CurrentHp = NewCurrentHp;

	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}

	if (HpStat)
	{
		HpStat->SetText(FText::FromString(GetHpStatText()));
	}
}

FString UFVHpBarWidget::GetHpStatText()
{
	return FString::Printf(TEXT("%.0f/%.0f"), CurrentHp, MaxHp);
}