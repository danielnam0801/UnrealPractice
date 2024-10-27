// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FVHUDWidget.h"
#include "FVHpBarWidget.h"
#include "Interface/FVCharacterHUDInterface.h"

UFVHUDWidget::UFVHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFVHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UFVHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UFVHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	IFVCharacterHUDInterface* HUDPawn = Cast<IFVCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
}
