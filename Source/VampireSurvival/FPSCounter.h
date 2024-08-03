// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EngineGlobals.h"
#include "FPSCounter.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API AFPSCounter : public AActor
{
	GENERATED_BODY()
private:

    float MinFPS = 1000;

    //Constructor
    AFPSCounter()
    {
        PrimaryActorTick.bCanEverTick = false;
    }

    //BeginPlay
    virtual void BeginPlay() override
    {
        Super::BeginPlay();

        //Esecuted only in editor
        #if WITH_EDITOR
            //Set a timer to call UpdateFPS() every second
            GetWorldTimerManager().SetTimer(TimerHandle_FPSUpdate, this, &AFPSCounter::UpdateFPS, 1.0f, true);
        #endif
    }

    //Write the current Fps and the Lowest Fps on screen
    void UpdateFPS()
    {
        //calculate the FPS
        float FPS = 1.0f / GetWorld()->GetDeltaSeconds();
        
        //Check if the FPS is Lower of MinFPS
        if (FPS < MinFPS)
        {
            //Set new MinFPS
            MinFPS = FPS;
        }

        //Write the FPS on screen
        GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::White, FString::Printf(TEXT("FPS: %.2f ,min FPS: %.2f"), FPS, MinFPS));
    }

    //Timer
    FTimerHandle TimerHandle_FPSUpdate;
};
