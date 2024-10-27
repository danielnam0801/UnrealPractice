// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FVCharacterStat.h"
#include "FVGameSingleton.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API UFVGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UFVGameSingleton();
	static UFVGameSingleton& Get();

	// Character Stat Data Section
public:
	FORCEINLINE FFVCharacterStat GetCharacterStat(int32 InLevel) const
	{
		return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FFVCharacterStat();
	}

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FFVCharacterStat> CharacterStatTable;
};
