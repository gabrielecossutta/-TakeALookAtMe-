#pragma once


//------------------------------------------------------------------Reusable Culling System------------------------------------------------------------------

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
