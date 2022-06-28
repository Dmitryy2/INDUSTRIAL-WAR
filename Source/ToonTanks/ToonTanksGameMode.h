// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <stdbool.h>

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"


UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	void ActorDied(AActor* DeadActor);

	void IncreaseTowersNum(){TowersNum++;}
	int32 GetTowersNum() const {return TowersNum;}

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	
	UFUNCTION(BlueprintImplementableEvent)
	void EndGame(bool bGameWon);

private:

	class ATank* Tank = nullptr;

	class AToonTanksPlayerController* PlayerController = nullptr;

	float StartDelay  = 3.5f;

	void HandleGameStart();
	
	UPROPERTY(EditAnywhere)
	int32 TowersNum = 0;

};
