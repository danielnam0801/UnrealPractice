// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AttackInRange.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API UBTDecorator_AttackInRange : public UBTDecorator
{
	GENERATED_BODY()
// Fill out your copyright notice in the Description page of Project Settings.

	UBTDecorator_AttackInRange();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
