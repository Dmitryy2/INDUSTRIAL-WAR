// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AProjectile::AProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Component");
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");

	ProjectileMovementComponent->InitialSpeed = ProjectileInitialSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileMaxSpeed;

	TrailParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("Trail Particle Component");
	TrailParticleComponent->SetupAttachment(RootComponent);
	
	ProjectileMovementComponent->ProjectileGravityScale = 0.f; // гравитация
}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
	
	
}


void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

	if(!GetOwner())
	{
		Destroy();
		return;
	} 

	if(OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

	
		
		UGameplayStatics::ApplyDamage(
		OtherActor,
		Damage,
		GetOwner()->GetInstigatorController(),
		this,
		UDamageType::StaticClass());
	}

	if(HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,
		HitParticle,
		GetActorLocation(),
		GetActorRotation());
	}
	
	Destroy();
}
