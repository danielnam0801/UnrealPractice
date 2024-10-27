// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetMoveSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API UBTService_SetMoveSpeed : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SetMoveSpeed();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float Speed;
};
