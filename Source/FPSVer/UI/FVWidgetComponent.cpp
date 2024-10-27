// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FVWidgetComponent.h"
#include "UI/FVUserWidget.h"

void UFVWidgetComponent::InitWidget()
{
	// UserWidget ���� �Ϸ�
	Super::InitWidget();

	UFVUserWidget* FVUserWidget = Cast<UFVUserWidget>(GetWidget());
	if (FVUserWidget)
	{
		FVUserWidget->SetOwningActor(GetOwner());
	}
}
