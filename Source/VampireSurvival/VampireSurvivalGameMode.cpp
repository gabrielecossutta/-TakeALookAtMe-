// Copyright Epic Games, Inc. All Rights Reserved.

#include "VampireSurvivalGameMode.h"
#include "VampireSurvivalCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BPBaseEnemy.h"
#include "Engine/TargetPoint.h"
#include "EngineUtils.h"
#include "UObject/Class.h"
#include "AIControllerEnemy.h"
AVampireSurvivalGameMode::AVampireSurvivalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnBPClass.Class;
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AVampireSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetSpawners();
}

//Find and return all the ATargetPoint in the level and put it in a TArray
TArray<class ATargetPoint*> AVampireSurvivalGameMode::GetSpawners()
{
	for (TActorIterator<ATargetPoint> It(GetWorld()); It; ++It)
	{
		TargetPoints.Add(*It);
	}
	return TargetPoints;
}

//Return a random Spawner
class ATargetPoint* AVampireSurvivalGameMode::GetRandomTarget()
{
	return AVampireSurvivalGameMode::TargetPoints[FMath::RandRange(0, TargetPoints.Num() - 1)];
}
