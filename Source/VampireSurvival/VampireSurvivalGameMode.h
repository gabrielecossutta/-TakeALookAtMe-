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

public:

	AVampireSurvivalGameMode();

	UPROPERTY(EditAnywhere)
	TArray<class ATargetPoint*> TargetPoints;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABPBaseEnemy>> Enemys;

	UFUNCTION(BlueprintCallable)
	void SetEnemys(TArray<TSubclassOf<ABPBaseEnemy>> NewEnemys);

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<class ATargetPoint*> GetSpawners();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION()
	class ATargetPoint* GetRandomTarget();

};



