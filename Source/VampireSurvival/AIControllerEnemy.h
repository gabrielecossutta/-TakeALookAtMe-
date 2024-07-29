// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVAL_API AAIControllerEnemy : public AAIController
{
	GENERATED_BODY()

protected:


	void BeginPlay() override;
	void OnPossess(APawn* InPawn);
	void Tick(float DeltaTime) override;
public:
	//UPROPERTY(EditAnywhere)
	//UBehaviorTree* AIBTAsset;
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BTAsset;

	UFUNCTION(BlueprintCallable)
	UBlackboardComponent* GetBlackboardComponents();


};
