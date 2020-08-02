// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:

	APawnBase();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

private:

    UPROPERTY()
    UCapsuleComponent* CapsuleComponent = nullptr;

    UPROPERTY()
    UStaticMeshComponent* BaseMesh = nullptr;

    UPROPERTY()
    UStaticMeshComponent* TurretMesh = nullptr;

    UPROPERTY()
    USceneComponent* ProjectileSpawnPoint = nullptr;

};
