// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UCameraShake;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AProjectileBase();

    virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UParticleSystemComponent* TrailParticle = nullptr;

    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* HitParticle = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    TSubclassOf<UDamageType> DamageType;

    UPROPERTY(EditAnywhere, Category = "Effects")
    USoundBase* LaunchSound;

    UPROPERTY(EditAnywhere, Category = "Effects")
    USoundBase* HitSound;

    UPROPERTY(EditAnywhere, Category = "Effects")
    TSubclassOf<UCameraShake> HitShake = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MovementSpeed = 1300.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
    float Damage = 50.f;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* Actor,
               UPrimitiveComponent* OtherHitComp, FVector NormalImpulse,
               const FHitResult& HitResult);
};
