// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FVWidgetInteface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFVWidgetInteface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSVER_API IFVWidgetInteface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupCharacterWidget(class UFVUserWidget* InUserWidget) = 0;
};
