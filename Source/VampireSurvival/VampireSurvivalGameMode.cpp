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


void AVampireSurvivalGameMode::SetEnemys(TArray<TSubclassOf<ABPBaseEnemy>> NewEnemys)
{
	Enemys = NewEnemys;
}

void AVampireSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetSpawners();
}



TArray<class ATargetPoint*> AVampireSurvivalGameMode::GetSpawners()
{
	TargetPoints.Empty();

	for (TActorIterator<ATargetPoint> It(GetWorld()); It; ++It)
	{
		TargetPoints.Add(*It);
	}
	return TargetPoints;
}

class ATargetPoint* AVampireSurvivalGameMode::GetRandomTarget()
{
	return AVampireSurvivalGameMode::TargetPoints[FMath::RandRange(0, TargetPoints.Num() - 1)];
}

void AVampireSurvivalGameMode::SpawnEnemy()
{
    if (Enemys.Num() > 0)
    {
        // Seleziona un indice casuale
        int RandomIndex = FMath::RandRange(0, Enemys.Num() - 1);

        // Ottieni la classe del nemico da spawnare
        TSubclassOf<ABPBaseEnemy> EnemyClass = Enemys[RandomIndex];

        // Ottieni una posizione casuale nel mondo (modifica GetRandomTarget() come necessario)
        FVector SpawnLocation = GetRandomTarget()->GetActorLocation();
        FRotator SpawnRotation = FRotator::ZeroRotator;

        // Parametri per il metodo SpawnActor
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        // Spawna il nemico
        ABPBaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABPBaseEnemy>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);

        // Controlla se il nemico è stato spawnato correttamente
        if (SpawnedEnemy)
        {
            UE_LOG(LogTemp, Warning, TEXT("Nemico spawnato con successo!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Errore durante lo spawn del nemico."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Nessun nemico disponibile nella lista."));
    }
}