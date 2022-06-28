// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Animation")
	class UParticleSystemComponent* TrailParticleComponent = nullptr;

	UPROPERTY(EditAnywhere, Category="Combat", BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float Damage = 25.f; //урон

	UPROPERTY(EditAnywhere, Category="Combat")
	float ProjectileMaxSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	float ProjectileInitialSpeed = 1.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category="Animation")
	class UParticleSystem* HitParticle = nullptr;

	UPROPERTY(EditAnywhere, Category="Animation")
	USoundBase* LaunchSound = nullptr;

	UPROPERTY(EditAnywhere, Category="Animation")
	USoundBase* HitSound = nullptr;


	
};
