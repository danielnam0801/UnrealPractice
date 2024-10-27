// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/FVCharStatActorComponent.h"
#include "GameData/FVGameSingleton.h"


// Sets default values for this component's properties
UFVCharStatActorComponent::UFVCharStatActorComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.0f;

	bWantsInitializeComponent = true;
}


// Called when the game starts
void UFVCharStatActorComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UFVCharStatActorComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UFVCharStatActorComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}

void UFVCharStatActorComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UFVGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(UFVGameSingleton::Get().GetCharacterStat(CurrentLevel));
	check(BaseStat.MaxHp > 0);
}

float UFVCharStatActorComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);

	// ����ϴ� ���� ������ ���� ��� ���� ó��
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}
