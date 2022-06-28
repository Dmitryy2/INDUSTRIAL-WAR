// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "ToonTanksGameMode.h"

ATower::ATower()
{
	Health = 100.f; 
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	GameModeBase = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	GameModeBase->IncreaseTowersNum();

	TowerLocation = GetOwner()->GetActorLocation();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	

	GetWorldTimerManager().SetTimer(FireTimer, this, &ATower::CheckFireConditions, FireRate, true);

}

//отслеживаем позицию игрока
void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(InRange())
	{
		FVector TargetLocation = PlayerTank->GetActorLocation();
		RotateTurret(TargetLocation);
	}
}
//определяем расстояние до игрока
const bool ATower::InRange()
{
	if(PlayerTank)
	{
		float DistanceToTank = FVector::Dist(TowerLocation, PlayerTank->GetActorLocation());

		if(DistanceToTank <= TowerRange)
		{
			return true;
		}
	}
	return false;
}
// если игрок в зоне видимости открываем по нему огонь
void ATower::CheckFireConditions()
{
	if(!PlayerTank){ return;}
	
	if(InRange() && PlayerTank->GetbAlive())
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}



