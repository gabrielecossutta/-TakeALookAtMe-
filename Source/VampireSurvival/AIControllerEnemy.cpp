// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerEnemy.h"
#include "BPBaseEnemy.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIControllerEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Get a pointer of the Enemy
	ABPBaseEnemy* Enemy = Cast<ABPBaseEnemy>(GetPawn());

	//Check if the enemy is Valid and if he has a BehaviourTree
	if (Enemy && Enemy->BehaviorTree)
	{
		//Start the BheaviourTree
		RunBehaviorTree(Enemy->BehaviorTree);
		
		//Assign the Player to the "Player" BlackboardComponent
		GetBlackboardComponent()->SetValueAsObject("Player", UGameplayStatics::GetPlayerCharacter(this, 0));
	}
}

void AAIControllerEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	//-----------------------------if using the PoolingSystem you dont need that, activate if u have to spawn enemy-----------------------------
	//ABPBaseEnemy* Enemy = Cast<ABPBaseEnemy>(InPawn);
	//if (Enemy && Enemy->BehaviorTree)
	//{
	//	RunBehaviorTree(Enemy->BehaviorTree);
	//	GetBlackboardComponent()->SetValueAsObject("Player", UGameplayStatics::GetPlayerCharacter(this, 0));
	//}
}

void AAIControllerEnemy::Tick(float DeltaTime)
{
}

//Return the BlackboardComponent
UBlackboardComponent* AAIControllerEnemy::GetBlackboardComponents()
{
	return GetBlackboardComponent();
}
