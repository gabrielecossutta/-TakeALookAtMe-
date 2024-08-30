// Fill out your copyright notice in the Description page of Project Settings.

//------------------------------------------------------------Just a empty component to find PoolingCharacter------------------------------------------------------------
#include "CullingComponent.h"

// Sets default values for this component's properties
UCullingComponent::UCullingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UCullingComponent::~UCullingComponent()
{
}

// Called when the game starts
void UCullingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UCullingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

