// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FVCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "AI/FVCharacterAIInterface.h"
#include "FVCharacterNonPlayer.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class FPSVER_API AFVCharacterNonPlayer : public AFVCharacterBase, public IFVCharacterAIInterface
{
	GENERATED_BODY()

public:
	AFVCharacterNonPlayer();
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void NotifyComboActionEnd() override;

	// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void AttackByAI() override;
	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;

	FAICharacterAttackFinished OnAttackFinished;

protected:
	virtual void SetDead() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
