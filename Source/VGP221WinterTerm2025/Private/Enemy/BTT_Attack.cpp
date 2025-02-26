// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTT_Attack.h"

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Method 1: Using Gameplay statics to get player character
	// AFPSCharacter* Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Method 2: Using blackboard value
	AFPSCharacter* Player = Cast<AFPSCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("PlayerTarget")));

	// Test code to hurt the player
	float DamageAmount = 1.0f;

	// Get AI Controller
	AEnemyAIController* AIAOwner = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	// Damage Method 1: Just call the function directly
	// Player->Damage(DamageAmount);

	// Damage Method 2: Apply Damage
	UGameplayStatics::ApplyDamage(Player, DamageAmount, AIAOwner, AIAOwner->GetPawn(), UDamageType::StaticClass());

	return EBTNodeResult::Succeeded;
}
