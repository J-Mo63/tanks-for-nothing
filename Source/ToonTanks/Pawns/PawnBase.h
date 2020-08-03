// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class UCameraShake;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:

	APawnBase();

    virtual void HandleDestruction();

private:
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* CapsuleComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BaseMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* TurretMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* ProjectileSpawnPoint = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UHealthComponent* HealthComponent = nullptr;

    // Other Fields
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AProjectileBase> ProjectileClass = nullptr;

    UPROPERTY(EditAnywhere, Category = "Effects")
    TSubclassOf<UCameraShake> DeathShake = nullptr;

    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* DeathParticle = nullptr;

    UPROPERTY(EditAnywhere, Category = "Effects")
    USoundBase* DeathSound;

protected:

    void RotateTurret(FVector LookAtTarget);

    void Fire();
};
