
//------------------------------------------------------------------Reusable Pooling System------------------------------------------------------------------

#include "PoolingSystem.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PoolingComponent.h" 
#include "Kismet/GameplayStatics.h"


//Constructor
APoolingSystem::APoolingSystem()
{
 	// Set this actor to not call Tick()
	PrimaryActorTick.bCanEverTick = false;
}

//Destructor
APoolingSystem::~APoolingSystem()
{
}

//BeginPlay
void APoolingSystem::BeginPlay()
{
	Super::BeginPlay();

	//Initialize the DormentCharacterPool
	InizializePool();
}

//Tick
void APoolingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Return an available enemy from the DormentCharacterPool
ACharacter* APoolingSystem::GetEnemy(FVector SpawnerLocation)
{
	//Check if there are Character available in the DormentCharacterPool
	if (DormantCharacterPool.Num() > 0)
	{
		//Get a random Character from the DormentCharacterPool
		int32 IndexPool = GetRandomPoolNumber();
		RandomCharacter = DormantCharacterPool[IndexPool];

		//Add the Character in the ActiveCharacterPool
		AddActivePool(RandomCharacter, SpawnerLocation);

		//return the Character
		return RandomCharacter;
	}

	//return NULL if the DormentCharacterPool is empty
	return nullptr;
}

//Called when a Enemy is choose from the DormentCharacterPool, Here the enemy is Activated (Render, Collision, Location)
void APoolingSystem::ActivateEnemy(ACharacter* Character, FVector SpawnerLocation)
{
	//Check if the Character is valid
	if (Character)
	{
		Character->SetActorHiddenInGame(false); //Show the character
		Character->SetActorEnableCollision(true); //Activate collision
		Character->SetActorLocation(SpawnerLocation); // Set character's location to SpawnerLocation

		//Find and check the Character Movement Component of the Character 
		UCharacterMovementComponent* CharacterMovement = Character->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement)
		{
			//Set the Character Movement Component mode to walking
			CharacterMovement->SetMovementMode(MOVE_Walking); 
		}
	}
}

//Called when a Enemy is killed, Here the enemy is Deactivated (Render, Collision, Location)
void APoolingSystem::DisableEnemy(ACharacter* Character)
{
	//Check if the Character is valid
	if (Character)
	{
		//Fixed position to hide the Character
		FVector PoolingLocation(0, 0, -1000); 

		Character->SetActorHiddenInGame(true); //Hide the Character
		Character->SetActorEnableCollision(false); //Disable Character collision
		Character->SetActorLocation(PoolingLocation); //Set Character location to PoolingLocation

		//Find and check the Character movement component of the Character 
		UCharacterMovementComponent* CharacterMovement = Character->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement)
		{
			//Disable the Character movement component
			CharacterMovement->DisableMovement();

			//Remove the Character from the ActiveCharacterPool
			ActiveCharacterPool.Remove(Character);

			//Add the Character to the DormentCharacterPool
			DormantCharacterPool.Add(Character);
		}
	}
}

//Add the choosen Character to the ActiveCharacterPool
void APoolingSystem::AddActivePool(ACharacter* Character, FVector SpawnerLocation)
{
	//Remove the Character from the DormantCharacterPool
	DormantCharacterPool.Remove(Character);

	//Add the Character in the ActiveCharacterPool
	ActiveCharacterPool.Add(Character);
	
	//Active the Character
	ActivateEnemy(Character, SpawnerLocation);
}

//Initialize the DormentCharacterPool with all the enemy in the level
void APoolingSystem::InizializePool()
{
	//TArray of AActor
	TArray<AActor*> ActorsFound;

	//Find all the Actors in the world derivated from ACharacter and fill the TArray
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), ActorsFound);

	//For every Actor in the TArray we check if they have a UPoolingComponent
	for (AActor* ActorFound : ActorsFound)
	{
		//Cast Actor to ACharacter
		ACharacter* CharacterFound = Cast<ACharacter> (ActorFound);

		if (CharacterFound->FindComponentByClass<UPoolingComponent>())
		{
			//Add the Character with the PoolingComponent to the DormantCharacterPool
			DormantCharacterPool.Add(CharacterFound);

			//Deactivate the Character
			DisableEnemy(CharacterFound);
		}
	}
}

//Return a random integer from 0 to DormentCharacterPool-1
int APoolingSystem::GetRandomPoolNumber()
{
	return FMath::RandRange(0, DormantCharacterPool.Num() - 1);
}