// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if( PlayerController != nullptr)
    {
        //PlayerController->GameHasEnded(nullptr, false);
        EndGame(false);
    }

    // For loop over ShooterAI in World:
    for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->IsDead())     // Is not dead?
        {
            return; // early return
        }
    }
    // no early return = End game
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner && Controller->IsPlayerController());
    }
}
