#pragma once


//------------------------------------------------------------------Reusable Pooling System------------------------------------------------------------------

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
