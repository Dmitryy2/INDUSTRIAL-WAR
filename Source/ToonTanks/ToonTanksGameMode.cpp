// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	
}


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	//если умер игрок заканчиваем игру пражением
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if(PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
			EndGame(false);
		}
	}
	//если нет башен то заканчиваем игру победой
	else if(auto DestroyedTower = Cast<ATower>(DeadActor))
	{
		TowersNum--;
		DestroyedTower->HandleDestruction();
                
		if (TowersNum <= 0)
		{
			EndGame(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	PlayerController = Cast<AToonTanksPlayerController>(
			UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
		
	if(PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);

		FTimerHandle GameStartTimer;

		FTimerDelegate GameStartTimerDelegate = FTimerDelegate::CreateUObject(
			PlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);

		GetWorldTimerManager().SetTimer(GameStartTimer, GameStartTimerDelegate, StartDelay, false);
	}

	
}

