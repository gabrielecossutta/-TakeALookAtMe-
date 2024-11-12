# ⭐TakeALookAtMe⭐
 *A Project Were I Want To Put Everything That I Have Learn In A Game (UnrealEngine5 C++)*

What I have implemented so far:

 [**CULLING**](#CULLING)
 
 [**POOLING**](#POOLING)


 
________________

 # CULLING
![Culling](https://github.com/user-attachments/assets/479c5108-4443-4b27-ab5f-e6c597104f9b)

### CullingSystem.cpp
``` cpp
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

```

### CullingSystem.h
``` cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CullingSystem.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API ACullingSystem : public AActor
{
	
	GENERATED_BODY()
private:	

	//Constructor: Sets default values
	ACullingSystem();

	//Destructor: Called when the instance is destroyed
	~ACullingSystem();

	//BeginPlay: Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Tick: Called every frame
	virtual void Tick(float DeltaTime) override;

	//TArray conteing all the Actor with a UCullingComponent
	TArray<AActor*> AllCullingActor;

	//Player Reference for Position
	ACharacter* PlayerReference;

	//CullingDegrees FOV + some Degrees for the culling see https://github.com/gabrielecossutta/-TakeALookAtMe-?tab=readme-ov-file#CULLING
	float FOVDegrees;

	//Method for calling CheckIfInfront for every Actor
	void CheckActors();

	//Method that return a boolean value indicating whether the enemy is in front of the player
	bool CheckIfInFront(AActor* ActorToCheck);

	//Method to initialize the AllCullingActor
	void FillArray();
	

};

```
 # POOLING
![Pooling](https://github.com/user-attachments/assets/e6cf8d7c-9462-426f-89f5-337a0b606472)

### PoolingSystem.cpp
``` cpp
#include "PoolingSystem.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PoolingComponent.h" 
#include "Kismet/GameplayStatics.h"

//Constructor: Sets default values
APoolingSystem::APoolingSystem()
{
 	// Set this actor to not call Tick()
	PrimaryActorTick.bCanEverTick = false;
}

//Destructor: Called when the instance is destroyed
APoolingSystem::~APoolingSystem()
{
}

//BeginPlay: Called when the game starts or when spawned
void APoolingSystem::BeginPlay()
{
	Super::BeginPlay();

	//Initialize the DormentCharacterPool
	InizializePool();
}

//Tick: Called every frame
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
```
### PoolingSystem.h
``` cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolingSystem.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API APoolingSystem : public AActor
{
	GENERATED_BODY()

private:

	//TArray of all the Dormant Character
	UPROPERTY(VisibleInstanceOnly)
	TArray<ACharacter*> DormantCharacterPool;

	//TArray of all the Active Character
	UPROPERTY(VisibleInstanceOnly)
	TArray<ACharacter*> ActiveCharacterPool; 

	//Random Character from the DormantCharacterPool
	ACharacter* RandomCharacter;

	//Return a Character from the DormantCharacterPool
	UFUNCTION(BlueprintCallable, Category = "Pooling")
	ACharacter* GetEnemy(FVector SpawnerLocation); 

	//Active a DormantCharacter
	void ActivateEnemy(ACharacter* Character, FVector SpawnerLocation); 

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	//Deactivate a Active Character
	void DisableEnemy(ACharacter* Character); 

	//Add a Character in the ActiveCharacterPool
	void AddActivePool(ACharacter* Character, FVector SpawnerLocation); 

	//Inizialize the DormantCharacterPool with all the Character with a PoolingComponent
	void InizializePool(); 

	//Return a integer from 0 to DormantCharacterPool
	int GetRandomPoolNumber(); 

	// BeginPlay: Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Constructor: Sets default values
	APoolingSystem();

	//Destructor: Called when the instance is destroyed
	~APoolingSystem();

	//Tick: Called every frame
	virtual void Tick(float DeltaTime) override;
};


```
