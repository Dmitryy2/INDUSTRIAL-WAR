// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const {return  PlayerController;}

	bool GetbAlive() {return bAlive;}


private:

	UPROPERTY(VisibleAnywhere, Category="Pawn Core Setup")
	class USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Pawn Core Setup")
	class UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, Category="Combat", BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float TankMoveSpeed = 350.f;//скорость танка вперд назад

	void MoveTank(float Value);

	UPROPERTY(EditAnywhere, Category="Combat", BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float TankTurnSpeed = 75.f;//скорость развората на месте

	void TurnTank(float Value);

	APlayerController* PlayerController = nullptr;

	FHitResult CursorHit;

	bool bAlive = true;
};
