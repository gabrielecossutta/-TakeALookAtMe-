// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BPBaseEnemy.h"
#include "VampireSurvivalGameMode.generated.h"

UCLASS(minimalapi)
class AVampireSurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	//Constructor
	AVampireSurvivalGameMode();

	//BeginPlay
	void BeginPlay() override;

	//Array of TargetPoints
	TArray<class ATargetPoint*> TargetPoints;

	//Return all the Spawner
	TArray<class ATargetPoint*> GetSpawners();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	//Return a random Target
	class ATargetPoint* GetRandomTarget();

};



