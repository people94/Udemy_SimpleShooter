// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterCharacter.h"
#include "AIController.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* OwnerController = OwnerComp.GetAIOwner();
    if(OwnerController == nullptr) return EBTNodeResult::Failed;

    AShooterCharacter* OwnerPawn = Cast<AShooterCharacter>(OwnerController->GetPawn());
    if(OwnerPawn == nullptr) return EBTNodeResult::Failed;

    OwnerPawn->StartFire();
    
    return EBTNodeResult::Succeeded;
}
