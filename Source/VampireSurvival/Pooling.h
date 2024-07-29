// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <utility>
#include "CoreMinimal.h"

/**
 * 
 */
class VAMPIRESURVIVAL_API Pooling
{public:
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
	ACharacter* GetEnemy();

	

	UFUNCTION(BlueprintCallable)
	//character
	void ActivateEnemy(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	//character
	void DisableEnemy(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	//character
	void AddActivePool(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	//character
	void RemoveActivePool(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	void InizializePool();

	UFUNCTION(BlueprintCallable)
	//character
	int GetRandomPoolNumber();


public:
	
	Pooling();
	~Pooling();
};
