// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* Controller, AActor* DamagingActor)
{
    if (Damage == 0.f || Health <= 0.f) { return; }

    Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);

    if (Health <= 0)
    {
        if (GameModeRef)
        {
            GameModeRef->ActorDied(GetOwner());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Health component has no reference to game mode!"))
        }
    }
}

