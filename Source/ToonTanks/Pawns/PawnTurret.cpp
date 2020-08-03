// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PawnTank.h"
#include "TimerManager.h"

APawnTurret::APawnTurret()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this,
                                           &APawnTurret::CheckFireCondition, FireRate, true);

    Player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}


void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if (!Player) { return 0.f; }
    return FVector::Dist(Player->GetActorLocation(), GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    if (Player && ReturnDistanceToPlayer() <= FireRange)
    {
        UE_LOG(LogTemp, Warning, TEXT("Firing"))
    }
}