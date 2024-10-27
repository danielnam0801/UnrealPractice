// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FVCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Physics/FVCollision.h"
#include "CharacterStat/FVCharStatActorComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/WidgetComponent.h"
#include "UI/FVWidgetComponent.h"
#include "UI/FVHpBarWidget.h"


// Sets default values
AFVCharacterBase::AFVCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement Component
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Mesh Component
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	// ���̷�Ż �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	// �ִ� �ν��Ͻ� Ŭ���� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClassRef(TEXT("/Game/Animation/ABP_Enemy.ABP_Enemy_C"));
	if (AnimClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimClassRef.Class);
	}

	// �ִϸ��̼� ��Ÿ��
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Game/Animation/AM_EnemyAttack.AM_EnemyAttack"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/Animation/AM_Dead.AM_Dead"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}


	// Stat Component 
	Stat = CreateDefaultSubobject<UFVCharStatActorComponent>(TEXT("Stat"));

	//// HpBar Widget Component
	/*HpBar = CreateDefaultSubobject<UFVWidgetComponent>(TEXT("HpBarWidget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWigetRef(TEXT("/Game/UI/WBP_HpbarPlayer.WBP_HpbarPlayer_C"));

	if (HpBarWigetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWigetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}*/
}

void AFVCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHpZero.AddUObject(this, &AFVCharacterBase::SetDead);
	Stat->OnStatChanged.AddUObject(this, &AFVCharacterBase::ApplyStat);
}

int32 AFVCharacterBase::GetLevel()
{
	//return int32();
	return Stat->GetCurrentLevel();
}

void AFVCharacterBase::SetLevel(int32 InNewLevel)
{
	Stat->SetLevelStat(InNewLevel);
}

void AFVCharacterBase::ApplyStat(const FFVCharacterStat& BaseStat, const FFVCharacterStat& ModifierStat)
{
	float MovementSpeed = (BaseStat + ModifierStat).MovementSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

void AFVCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	//HpBar->SetHiddenInGame(true);
}

void AFVCharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(DeadMontage, 1.0f);
	}
}

void AFVCharacterBase::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = Stat->GetTotalStat().AttackRange;
	const float AttackRadius = Stat->GetAttackRadius();
	const float AttackDamage = Stat->GetTotalStat().Attack;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_FVACTION, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)
	{
		// �浹 ����
		UGameplayStatics::ApplyDamage(OutHitResult.GetActor(), AttackDamage, GetController(), nullptr, nullptr);
	}
//#if ENABLE_DRAW_DEBUG
//	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
//	float CapsuleHalfHeight = AttackRange * 0.5f;
//	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
//
//	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
//#endif
}

float AFVCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Stat->ApplyDamage(DamageAmount);
	return DamageAmount;
}

void AFVCharacterBase::ProcessComboCommand()
{
	// ù �޺� �Է� ��
	
	ComboActionBegin();
	return;
	
}

void AFVCharacterBase::ComboActionBegin()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	// Animation Setting
	const float AttackSpeedRate = Stat->GetTotalStat().AttackSpeed;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

	//// Montage End Delegate
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AFVCharacterBase::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);
}

void AFVCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsPropertyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	NotifyComboActionEnd();
}

void AFVCharacterBase::NotifyComboActionEnd()
{
}

void AFVCharacterBase::SetComboCheckTimer()
{
}

void AFVCharacterBase::ComboCheck()
{
}

void AFVCharacterBase::SetupCharacterWidget(UFVUserWidget* InUserWidget)
{
	UFVHpBarWidget* HpBarWidget = Cast<UFVHpBarWidget>(InUserWidget);
	if (HpBarWidget)
	{
		UE_LOG(LogTemp, Log, TEXT("SetUp"));
		HpBarWidget->UpdateStat(Stat->GetBaseStat(), Stat->GetModifierStat());
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp());

		// HpBarWidget�� UpdateHpBar�� Stat ������Ʈ�� Hp�� ���� �� ������ ȣ���Ѵ�.
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UFVHpBarWidget::UpdateHpBar);

		// Stat�� ���� �� �� ȣ��Ǵ� �Լ�
		Stat->OnStatChanged.AddUObject(HpBarWidget, &UFVHpBarWidget::UpdateStat);
	}
}

