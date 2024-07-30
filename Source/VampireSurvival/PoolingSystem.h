// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolingSystem.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API APoolingSystem : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<ACharacter*> CharacterPool;

	UPROPERTY(EditAnywhere)
	TArray<ACharacter*> ActiveCharacterPool;

	UPROPERTY(EditAnywhere)
	ACharacter* RandomCharacter;

	UPROPERTY(EditAnywhere)
	uint32 Size;

	UFUNCTION(BlueprintCallable)
	//character
	ACharacter* GetEnemy(FVector Spawner);



	UFUNCTION(BlueprintCallable)
	//character
	void ActivateEnemy(ACharacter* Character, FVector Spawner);

	UFUNCTION(BlueprintCallable)
	//character
	void DisableEnemy(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	//character
	void AddActivePool(ACharacter* Character, FVector Spawner);

	UFUNCTION(BlueprintCallable)
	//character
	void RemoveActivePool(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	void InizializePool();

	UFUNCTION(BlueprintCallable)
	//character
	int GetRandomPoolNumber();

public:	
	// Sets default values for this actor's properties
	APoolingSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
