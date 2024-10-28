// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if(bIsWinner)
    {
        UE_LOG(LogTemp, Warning, TEXT("You Win"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You Lose"));
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
