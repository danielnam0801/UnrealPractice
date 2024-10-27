// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/FVCharacterStat.h"
#include "FVCharStatActorComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangeDelegate, float /*CurrentHp*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FFVCharacterStat& /*BaseStat*/, const FFVCharacterStat& /*ModifierStat*/)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSVER_API UFVCharStatActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFVCharStatActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE float GetCurrentLevel() { return CurrentLevel; }
	FORCEINLINE float GetAttackRadius() { return AttackRadius; }
	FORCEINLINE const FFVCharacterStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FFVCharacterStat& GetModifierStat() const { return ModifierStat; }
	FORCEINLINE FFVCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }
	
	FORCEINLINE void SetBaseStat(const FFVCharacterStat& InBaseStat)
	{
		BaseStat = InBaseStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void SetModifierStat(const FFVCharacterStat& InModifierStat)
	{
		ModifierStat = InModifierStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void HealHp(float InHealAmount)
	{
		CurrentHp = FMath::Clamp(CurrentHp + InHealAmount, 0, GetTotalStat().MaxHp);
		OnHpChanged.Broadcast(CurrentHp);
	}

	FORCEINLINE void AddBaseStat(const FFVCharacterStat& InAddBaseStat)
	{
		BaseStat = BaseStat + InAddBaseStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	void SetHp(float NewHp);
	void SetLevelStat(int32 InNewLevel);

	float ApplyDamage(float InDamage);

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangeDelegate OnHpChanged;
	FOnStatChangedDelegate OnStatChanged;

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float AttackRadius;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	FFVCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	FFVCharacterStat ModifierStat;
};