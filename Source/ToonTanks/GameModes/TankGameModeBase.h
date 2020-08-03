// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"


class AActor;
class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

    void ActorDied(AActor* DeadActor);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
    int32 StartDelay = 4;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent)
    void GameStart();

    UFUNCTION(BlueprintImplementableEvent)
    void GameOver(bool PlayerWon);

private:

    APlayerControllerBase* PlayerControllerRef;

    APawnTank* PlayerTank;

    int32 TargetTurrets = 0;

    void HandleGameStart();

    void HandleGameOver(bool PlayerWon);

};
