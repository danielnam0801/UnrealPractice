// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/FVGameSingleton.h"


UFVGameSingleton::UFVGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Game/GameData/FVCharacterStatTable.FVCharacterStatTable"));
	if (DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FFVCharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UFVGameSingleton& UFVGameSingleton::Get()
{
	UFVGameSingleton* Singleton = CastChecked<UFVGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	return *NewObject<UFVGameSingleton>();
}
