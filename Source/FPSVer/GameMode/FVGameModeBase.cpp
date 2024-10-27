// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FVGameModeBase.h"
#include "Player/FVPlayerController.h"

AFVGameModeBase::AFVGameModeBase()
{
	//UGameInstance* GameInstance = 
	static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/FPSTutorial/Core/BP_Character.BP_Character_C"));

	if (ThirdPersonClassRef.Class)
	{
		DefaultPawnClass = ThirdPersonClassRef.Class;
	}

	//// PlayerControllerClass (Player)
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/FPSTutorial/Core/BP_Player_Controller.BP_Player_Controller_C"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
	
	bIsCleared = false;
}

void AFVGameModeBase::OnGameStart()
{
	
}

void AFVGameModeBase::OnPlayerScoreChanged(int32 NewPlayerScore)
{
	/*CurrentScore = NewPlayerScore;

	AABPlayerController* ABPlayerController = Cast<AABPlayerController>(GetWorld()->GetFirstPlayerController());
	if (ABPlayerController)
	{
		ABPlayerController->GameScoreChanged(CurrentScore);
	}

	if (CurrentScore >= ClearScore)
	{
		bIsCleared = true;

		if (ABPlayerController)
		{
			ABPlayerController->GameClear();
		}
	}*/
}

void AFVGameModeBase::OnPlayerDead()
{
	AFVPlayerController* AFVlayerController = Cast<AFVPlayerController>(GetWorld()->GetFirstPlayerController());
	if (AFVlayerController)
	{
		AFVlayerController->GameOver();
	}
}

bool AFVGameModeBase::IsGameCleared()
{
	return bIsCleared;
}
