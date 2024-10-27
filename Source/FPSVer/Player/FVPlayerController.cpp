// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FVPlayerController.h"
#include "UI/FVHUDWidget.h"
#include <Kismet/GameplayStatics.h>
//#include "ABSaveGame.h"


AFVPlayerController::AFVPlayerController()
{
	/*static ConstructorHelpers::FClassFinder<UFVHUDWidget> ABHUDWidgetRef(TEXT(""));
	if (ABHUDWidgetRef.Class)
	{
		FVHUDWidgetClass = ABHUDWidgetRef.Class;
	}*/
}

void AFVPlayerController::BeginPlay()
{
	//Super::BeginPlay();

	//FInputModeGameOnly GameOnlyInputMode;
	//SetInputMode(GameOnlyInputMode);

	//SaveGameInstance = Cast<UABSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player0"), 0));
	//if (SaveGameInstance == nullptr)
	//{
	//	SaveGameInstance = NewObject<UABSaveGame>();
	//	SaveGameInstance->RetryCount = 0;
	//}
	//SaveGameInstance->RetryCount++;

	//OnGameRetryCount(SaveGameInstance->RetryCount);

	//FVHUDWidget = CreateWidget<UFVHUDWidget>(this, FVHUDWidgetClass);
	//if (FVHUDWidget)
	//{
	//	FVHUDWidget->AddToViewport();
	//}
}

void AFVPlayerController::GameScoreChanged(int32 NewScore)
{
	OnScoreChanged(NewScore);
}

void AFVPlayerController::GameClear()
{
	OnGameClear();
}

void AFVPlayerController::GameOver()
{
	/*OnGameOver();

	if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Player0"), 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Save Game Error!"));
	}

	OnGameRetryCount(SaveGameInstance->RetryCount);*/
}
