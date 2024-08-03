// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BPBaseEnemy.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API ABPBaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:

	//Constructor
	ABPBaseEnemy();

	UPROPERTY(VisibleAnywhere)
	//BehaviorTree of the enemy
	class UBehaviorTree* BehaviorTree;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	//Enemy level
	float Level;

	UPROPERTY(EditAnywhere)
	//Xp reward for player
	float Xp;

	UPROPERTY(EditAnywhere)
	//Enemy Health (moltiply for Level)
	float Health;

	UPROPERTY(EditAnywhere)
	//Enemy Health (moltiply for Level)
	float Damage;

	UPROPERTY(EditAnywhere)
	//Enemy Speed
	float Speed;

	//StaticMesh of the Bullet of the enemy if he is a ranger
	UStaticMeshComponent* Ammo;

	//Animation of enemy attacking
	UAnimationAsset* AttackAnimation;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
