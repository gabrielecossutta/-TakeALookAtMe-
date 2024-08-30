// Fill out your copyright notice in the Description page of Project Settings.


#include "CullingSystem.h"
#include "CullingComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACullingSystem::ACullingSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACullingSystem::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerReference = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FillArray();

}

// Called every frame
void ACullingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckActors();
}

bool ACullingSystem::CheckIfInFront(AActor* ActorToCheck)
{
	float PlayerFOV = 130;
	
	//
	float DotProduct = FVector::DotProduct(PlayerReference->GetActorForwardVector(), (ActorToCheck->GetActorLocation()-PlayerReference->GetActorLocation()).GetSafeNormal());

	//
	float Angle = FMath::Acos(DotProduct) * (180.0f / PI);
	if (Angle <= PlayerFOV / 2.0f)
	{
		return true;
	}
	return false;
}

void ACullingSystem::CheckActors()
{
	for (AActor* Actor : AllActor)
	{
		if (CheckIfInFront(Actor))
		{
			Actor->SetActorHiddenInGame(false);
		}
		else
		{
			Actor->SetActorHiddenInGame(true);
		}
	}

}

void ACullingSystem::FillArray()
{
	TArray<AActor*> ActorsFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsFound);
	{
		for (AActor* Actor : ActorsFound)
		{
			if (Actor->FindComponentByClass<UCullingComponent>())
			{
				AllActor.Add(Actor);
			}
		}
		
	}
}
