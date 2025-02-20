// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTT_GetRandomPatrolLocation.h"

EBTNodeResult::Type UBTT_GetRandomPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 1. Get random point on the nav mesh
	// 2. Set the blackboard random patorl location to random point on nav mesh
	// 3. Return if succeed or not
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavArea) {
		AEnemyAIController* AIOwner = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
		NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), AIOwner->GetPawn()->GetActorLocation(), RandomLocation, 2000.0f);
	}
	else {
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("RandomPatrolLocation"), RandomLocation);

	return EBTNodeResult::Succeeded;
}
