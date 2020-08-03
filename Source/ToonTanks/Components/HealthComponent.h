// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class ATankGameModeBase;
class AController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UHealthComponent();

protected:

	virtual void BeginPlay() override;

    UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Controller, AActor* DamagingActor);

private:

    UPROPERTY(EditAnywhere)
    float DefaultHealth = 100.f;

    float Health = 0.f;

    ATankGameModeBase* GameModeRef;
		
};
