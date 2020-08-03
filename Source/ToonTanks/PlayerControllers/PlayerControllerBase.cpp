// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/Pawn.h"

void APlayerControllerBase::SetPlayerEnabledState(bool Enable)
{
    if (Enable)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = Enable;
}