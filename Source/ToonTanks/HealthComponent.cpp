// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"


UHealthComponent::UHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	OwnerActor = Cast<ABasePawn>(GetOwner());
	
}



void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	MaxHealth = OwnerActor->GetHealth();
	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}



void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//считаем урон
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{

	if(Damage <= 0) return;

	Health -= Damage;

	if(ToonTanksGameMode && Health <= 0)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}

