// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerEnemy.h"
#include "BPBaseEnemy.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
void AAIControllerEnemy::BeginPlay()
{
	Super::BeginPlay();
	ABPBaseEnemy* Enemy = Cast<ABPBaseEnemy>(GetPawn());
	if (Enemy && Enemy->BehaviorTree)
	{
		RunBehaviorTree(Enemy->BehaviorTree);
		GetBlackboardComponent()->SetValueAsObject("Player", UGameplayStatics::GetPlayerCharacter(this, 0));
	}
}

void AAIControllerEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	//-----------------------------Using the Pooling system you dont need that, activate if u have to spawn enemy -----------------------------
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

UBlackboardComponent* AAIControllerEnemy::GetBlackboardComponents()
{
	return GetBlackboardComponent();
}