// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"


#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


ABasePawn::ABasePawn()
{

	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	RootComponent = CapsuleComponent;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMeshComponent->SetupAttachment(RootComponent);

	TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMeshComponent->SetupAttachment(BaseMeshComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMeshComponent);

	
	
}


void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//определяем направление башни
void ABasePawn::RotateTurret(FVector TargetRotation)
{
	TargetRotation = TargetRotation - TurretMeshComponent->GetComponentLocation();
	
	FRotator TargetRotator = FRotator::ZeroRotator;
	TargetRotator.Yaw = TargetRotation.Rotation().Yaw;

	TurretMeshComponent->SetWorldRotation(TargetRotator);
	
}
//класс стрельбы
void ABasePawn::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		DefaultProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation());
	
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	if(DeathParticleSystem)
	{
		if (DeathSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		}

		if(DeathCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
		}
		
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticleSystem,
			GetActorLocation(),
			GetActorRotation());
	}
	
}


