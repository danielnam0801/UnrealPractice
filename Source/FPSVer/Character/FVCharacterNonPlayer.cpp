// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FVCharacterNonPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Physics/FVCollision.h"
#include <Engine/AssetManager.h>
#include "AI/FVAIController.h"
#include "CharacterStat/FVCharStatActorComponent.h"
#include <Components/WidgetComponent.h>
#include "UI/FVWidgetComponent.h"
#include "UI/FVHpBarWidget.h"

AFVCharacterNonPlayer::AFVCharacterNonPlayer()
{
	// AI
	AIControllerClass = AFVAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Capsule
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_FVCAPSULE);

	// Mesh
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	//GetMesh()->SetHiddenInGame(true);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/BookHeadMonster/Meshes/BookHeadMonster.BookHeadMonster"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/Animation/AM_Dead.AM_Dead"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	//// HpBar Widget Component
	//HpBar = CreateDefaultSubobject<UFVWidgetComponent>(TEXT("HpBarWidget"));
	//HpBar->SetupAttachment(GetMesh());
	//HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	//HpBar->SetHiddenInGame(true);
	//static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWigetRef(TEXT("/Game/UI/WBP_Hpbar.WBP_Hpbar_C"));

	//if (HpBarWigetRef.Class)
	//{
	//	HpBar->SetWidgetClass(HpBarWigetRef.Class);
	//	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	//	HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
	//	HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//}
	
	//// Stat Component 
	//Stat = CreateDefaultSubobject<UFVCharacterStatComponent>(TEXT("Stat"));

	//// HpBar Widget Component
	//HpBar = CreateDefaultSubobject<UFVWidgetComponent>(TEXT("HpBarWidget"));
	//HpBar->SetupAttachment(GetMesh());
	//HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));

	//static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWigetRef(TEXT("/Game/ArenaBattle/UI/WBP_HpBar.WBP_HpBar_C"));

	//if (HpBarWigetRef.Class)
	//{
	//	HpBar->SetWidgetClass(HpBarWigetRef.Class);
	//	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	//	HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
	//	HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//}
}

void AFVCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AFVCharacterNonPlayer::NotifyComboActionEnd()
{
	Super::NotifyComboActionEnd();
	OnAttackFinished.ExecuteIfBound();
}

float AFVCharacterNonPlayer::GetAIPatrolRadius()
{
	return 1000.0f;
}

float AFVCharacterNonPlayer::GetAIDetectRange()
{
	return 2500.0f;
}

float AFVCharacterNonPlayer::GetAIAttackRange()
{
	//return 500.f;
	return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius() * 2;
}

float AFVCharacterNonPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void AFVCharacterNonPlayer::AttackByAI()
{
	ProcessComboCommand();
}

void AFVCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AFVCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	AFVAIController* ABAIController = Cast<AFVAIController>(GetController());
	if (ABAIController)
	{
		ABAIController->StopAI();
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}

float AFVCharacterNonPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Stat->ApplyDamage(DamageAmount);
	
	return DamageAmount;
}
