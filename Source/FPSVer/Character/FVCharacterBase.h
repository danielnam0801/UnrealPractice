// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameData/FVCharacterStat.h"
#include "Interface/FVAnimationAttackInterface.h"
#include "Interface/FVWidgetInteface.h"
#include <UI/FVUserWidget.h>
#include "FVCharacterBase.generated.h"

UCLASS()
class FPSVER_API AFVCharacterBase : public ACharacter, public IFVAnimationAttackInterface, public IFVWidgetInteface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFVCharacterBase();

public:
	virtual void PostInitializeComponents() override;

	// Stat Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFVCharStatActorComponent> Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFVWidgetComponent> HpBar;

	virtual void SetupCharacterWidget(class UFVUserWidget* InUserWidget) override;

public:
	int32 GetLevel();
	void SetLevel(int32 InNewLevel);

	void ApplyStat(const FFVCharacterStat& BaseStat, const FFVCharacterStat& ModifierStat);

	// Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	float DeadEventDelayTime = 3.0f;

	virtual void SetDead();
	void PlayDeadAnimation();

	// Attack Hit Section
protected:
	virtual void AttackHitCheck() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Combo Action Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded);
	virtual void NotifyComboActionEnd();

	void SetComboCheckTimer();
	void ComboCheck();
};
