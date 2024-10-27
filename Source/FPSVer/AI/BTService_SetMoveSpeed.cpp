// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_SetMoveSpeed.h"
#include "FVAI.h"
#include "FVAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/FVCharacterAIInterface.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTService_SetMoveSpeed::UBTService_SetMoveSpeed()
{
}

void UBTService_SetMoveSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(ControllingPawn->GetMovementComponent());
	if (movement == nullptr)
		return;

	movement->MaxWalkSpeed = Speed;
}
