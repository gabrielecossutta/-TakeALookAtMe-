// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolingSystem.h"
#include "PoolingComponent.h" 
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
APoolingSystem::APoolingSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolingSystem::BeginPlay()
{
	Super::BeginPlay();
	InizializePool();
	
}

// Called every frame
void APoolingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

ACharacter* APoolingSystem::GetEnemy(FVector Spawner)
{
	if (CharacterPool.Num() > 0)
	{
		int32 IndexPool = GetRandomPoolNumber();
		RandomCharacter = CharacterPool[IndexPool];
		AddActivePool(RandomCharacter, Spawner);
		UE_LOG(LogTemp, Warning, TEXT("%d"),CharacterPool.Num());
		return RandomCharacter;
	}
	return nullptr;
}

void APoolingSystem::ActivateEnemy(ACharacter* Character, FVector Spawner)
{
	if (Character)
	{
		//Character->SetActorHiddenInGame(false); // Hide the character
		Character->SetActorEnableCollision(true); // Disable collision
		Character->SetActorTickEnabled(true); // Disable ticking
		Character->SetActorLocation(Spawner); // Set character's location to NewPosition

		// Disable character movement
		UCharacterMovementComponent* CharacterMovement = Character->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement)
		{
			CharacterMovement->SetMovementMode(MOVE_Walking); // Imposta il movimento come camminare (o altro, a seconda del tipo di movimento richiesto)
		}
	}
}

void APoolingSystem::DisableEnemy(ACharacter* Character)
{

	if (Character)
	{
		FVector NewPosition(10000, 100000, 0); // Fixed position to lock the character to
		//Character->SetActorHiddenInGame(true); // Hide the character
		Character->SetActorEnableCollision(false); // Disable collision
		Character->SetActorTickEnabled(false); // Disable ticking
		Character->SetActorLocation(NewPosition); // Set character's location to NewPosition

		// Disable character movement
		UCharacterMovementComponent* CharacterMovement = Character->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement)
		{
			CharacterMovement->DisableMovement();
			ActiveCharacterPool.Remove(Character);
			CharacterPool.Add(Character);
		}
	}
}

void APoolingSystem::AddActivePool(ACharacter* Character, FVector Spawner)
{
	CharacterPool.Remove(Character);
	ActiveCharacterPool.Add(Character);
	ActivateEnemy(Character, Spawner);
}

//migliorare o togliere
void APoolingSystem::RemoveActivePool(ACharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("-------------"), CharacterPool.Num());
	uint32 UniqueID = Character->GetUniqueID();
	for (ACharacter* CharacterToDeactivate : ActiveCharacterPool)
	{
		if (UniqueID == Character->GetUniqueID())
		{
			DisableEnemy(CharacterToDeactivate);

			ActiveCharacterPool.Remove(CharacterToDeactivate);
			CharacterPool.Add(CharacterToDeactivate);
		}
	}
}

void APoolingSystem::InizializePool()
{
	TArray<AActor*> ActorsFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), ActorsFound);
	for (AActor* ActorFound : ActorsFound)
	{
		ACharacter* CharacterFound = Cast<ACharacter> (ActorFound);
		if (CharacterFound->FindComponentByClass<UPoolingComponent>())
		{
				CharacterPool.Add(CharacterFound);
				DisableEnemy(CharacterFound);
		}
	}

}



int APoolingSystem::GetRandomPoolNumber()
{
	return FMath::RandRange(0, CharacterPool.Num() - 1);
}
