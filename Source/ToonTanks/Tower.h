// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

	ATower();

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction();
	

protected:

private:

	class ATank* PlayerTank = nullptr;

	FVector  TowerLocation;

	FTimerHandle FireTimer;

	const bool InRange();

	UPROPERTY(EditAnywhere, Category="Combat")
	float TowerRange = 1100.f; 
	
	UPROPERTY(EditAnywhere, Category="Combat")
	float FireRate = 1.5f; 

	void CheckFireConditions();

	class AToonTanksGameMode* GameModeBase = nullptr;

	

	
};
