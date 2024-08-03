// Fill out your copyright notice in the Description page of Project Settings.


#include "BPBaseEnemy.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ABPBaseEnemy::ABPBaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABPBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	//Set MaxWalkSpeet
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

// Called every frame
void ABPBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABPBaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

