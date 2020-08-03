// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
    FVector Cleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
    FVector Start = TurretMesh->GetComponentLocation();
    TurretMesh->SetWorldRotation((Cleaned - Start).Rotation());
}

void APawnBase::Fire()
{
    if (ProjectileClass)
    {
        AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
                ProjectileClass,
                ProjectileSpawnPoint->GetComponentLocation(),
                ProjectileSpawnPoint->GetComponentRotation());
        TempProjectile->SetOwner(this);
    }
}

void APawnBase::HandleDestruction()
{
    UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
    UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
    GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}