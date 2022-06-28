// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#define OUT

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	Health = 149.f;//хп танка



}
//управление танком
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &ATank::MoveTank);
	InputComponent->BindAxis("Turn", this, &ATank::TurnTank);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
	
}

void ATank::BeginPlay()
{
	Super::BeginPlay();


	PlayerController = Cast<APlayerController>(GetController());
}
//не позволят уйти мышке за пределы игры
void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			OUT CursorHit);



		RotateTurret(CursorHit.Location);
	}
	
	
}

//езда танка вперед назад
void ATank::MoveTank(float Value)
{

	FVector DeltaLocation = FVector::ZeroVector;
	
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaLocation.X = Value * DeltaTime * TankMoveSpeed;
	
	AddActorLocalOffset(DeltaLocation, true);
}
//разворот танка на месте и в движении
void ATank::TurnTank(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaRotation.Yaw = Value * DeltaTime * TankTurnSpeed;

	AddActorLocalRotation(DeltaRotation, true);
}
void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	bAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
}

