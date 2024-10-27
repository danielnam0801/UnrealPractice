// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FVAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPSVER_API AFVAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AFVAIController();

	void RunAI();
	void StopAI();

protected:
	// AIController°¡ Pawn¿¡ ºùÀÇµÆÀ» ¶§ È£Ãâ µÊ
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
