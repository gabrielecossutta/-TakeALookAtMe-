// Fill out your copyright notice in the Description page of Project Settings.


#include "CullingSystem.h"
#include "CullingComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


//Constructor: Sets default values
ACullingSystem::ACullingSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//Destructor: Called when the instance is destroyed
ACullingSystem::~ACullingSystem()
{
}

// BeginPlay: Called when the game starts or when spawned
void ACullingSystem::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerReference = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FillArray();

}

// Tick: Called every frame
void ACullingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckActors();
}

//Returns a boolean value indicating whether the enemy is in front of the player
bool ACullingSystem::CheckIfInFront(AActor* ActorToCheck)
{
	//Player field of view plus some angle
	float PlayerFOV = 130;

	//Directional Vector from Player to Enemy (normalized)
	float DotProduct = FVector::DotProduct(PlayerReference->GetActorForwardVector(), (ActorToCheck->GetActorLocation()-PlayerReference->GetActorLocation()).GetSafeNormal());

	//Convert the DotProduct to Radians
	float Radians = FMath::Acos(DotProduct);

	//Convert Radians to Angle
	float Angle = Radians * (180.0f / PI);

	//Check if the Angle is less than the half of PlayerFOV and is above the Pooling area
	if (Angle <= PlayerFOV / 2.0f && ActorToCheck->GetActorLocation().Z > -500)
	{
		//return true is less than PlayerFOV/2
		return true;
	}

	//Return true if greater than PlayerFOV / 2
	return false;
}

//For every actor with a CullingComponent call the CheckIfInFront() method
void ACullingSystem::CheckActors()
{
	//For each actor in the Array check if in front of
	for (AActor* Actor : AllCullingActor)
	{
		if (CheckIfInFront(Actor))
		{
			//If in front dont hide the Actor
			Actor->SetActorHiddenInGame(false);
		}
		else
		{
			//If not in front hide the Actor
			Actor->SetActorHiddenInGame(true);
		}
	}
}

//Initialize the DormentArray with all the actor that have a Culling Component
void ACullingSystem::FillArray()
{
	//TArray of AActor
	TArray<AActor*> ActorsFound;

	//Find all the Actors in the world derivated from AActor and fill the TArray
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsFound);
	{

		//For every Actor in the TArray we check if they have a UCullingComponent
		for (AActor* Actor : ActorsFound)
		{
			if (Actor->FindComponentByClass<UCullingComponent>())
			{
				//Add the Actor with the CullingComponent to the DormantPool
				AllCullingActor.Add(Actor);
			}
		}
	}
}
