// Fill out your copyright notice in the Description page of Project Settings.

//------------------------------------------------------------Just a empty component to find PoolingCharacter------------------------------------------------------------
#include "PoolingComponent.h"

// Sets default values for this component's properties
UPoolingComponent::UPoolingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UPoolingComponent::~UPoolingComponent()
{
}

// Called when the game starts
void UPoolingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UPoolingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

