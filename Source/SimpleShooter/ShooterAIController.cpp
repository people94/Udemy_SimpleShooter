// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    //SetFocus(PlayerPawn); // Tick에서 자동으로 Target보도록 시선돌려주는 듯. 그래서 한번만 호출해도됨.

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
     APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

//    // MoveToActor(PlayerPawn, 200); // 얘는 호출할때만 이동하는 거라서 Tick에서 호출해야함

     if(LineOfSightTo(PlayerPawn))
     {
//         SetFocus(PlayerPawn);
//         MoveToActor(PlayerPawn, AcceptanceRadius);
        // Setting PlayerLocation
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        // Setting lastknown
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
     }
     else
     {
//         ClearFocus(EAIFocusPriority::Gameplay);
//         StopMovement();
        // clear PlayerLocation
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
     }
}
