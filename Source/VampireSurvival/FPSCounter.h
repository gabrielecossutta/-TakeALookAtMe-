// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "FPSCounter.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API AFPSCounter : public AActor
{
	GENERATED_BODY()
private:
    float MinFps = 1000;

public:
    // Costruttore
    AFPSCounter()
    {
        PrimaryActorTick.bCanEverTick = false;
    }

    // Funzione per il tick
    virtual void BeginPlay() override
    {
        Super::BeginPlay();

        // Avvia il timer per aggiornare gli FPS ogni secondo
        GetWorldTimerManager().SetTimer(TimerHandle_FPSUpdate, this, &AFPSCounter::UpdateFPS, 1.0f, true);
    }

    // Funzione per aggiornare gli FPS
    void UpdateFPS()
    {
        float FPS = 1.0f / GetWorld()->GetDeltaSeconds();
        if (FPS < MinFps)
        {
            MinFps = FPS;
        }
        GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::White, FString::Printf(TEXT("FPS: %.2f ,min FPS: %.2f"), FPS, MinFps));
    }

private:
    FTimerHandle TimerHandle_FPSUpdate;
};
