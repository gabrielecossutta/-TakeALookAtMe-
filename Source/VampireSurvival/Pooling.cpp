// Fill out your copyright notice in the Description page of Project Settings.


#include "Pooling.h"
#include "GameFramework/Character.h"
ACharacter* Pooling::GetEnemy()
{
	int32 IndexPool = GetRandomPoolNumber();
	RandomCharacter = CharacterPool[IndexPool];
	AddActivePool(RandomCharacter);
	return RandomCharacter;
}

void Pooling::ActivateEnemy(ACharacter* Character)
{
	if (Character)
	{
		Character->SetActorHiddenInGame(true);
		Character->SetActorEnableCollision(true);
		Character->SetActorTickEnabled(true);
	}
}

void Pooling::DisableEnemy(ACharacter* Character)
{
	if (Character)
	{
		Character->SetActorHiddenInGame(false);
		Character->SetActorEnableCollision(false);
		Character->SetActorTickEnabled(false);
	}
}

void Pooling::AddActivePool(ACharacter* Character)
{
	ActiveCharacterPool.Add(Character);
	ActivateEnemy(Character);
}

void Pooling::RemoveActivePool(ACharacter* Character)
{
	ActiveCharacterPool.Remove(Character);
	DisableEnemy(Character);
	CharacterPool.Add(Character);
	uint32 UniqueID = Character->GetUniqueID();
	for (ACharacter* CharacterToDeactivate : ActiveCharacterPool)
	{
		if (CharacterToDeactivate == Character)
		{
			DisableEnemy(CharacterToDeactivate);
			ActiveCharacterPool.Remove(CharacterToDeactivate);
		}
	}
}

//void Pooling::AssigneUniqueID()
//{
//	for (ACharacter* Character : CharacterPool)
//	{
//		GetUniqueID
//	}
//}

int Pooling::GetRandomPoolNumber()
{
	return FMath::RandRange(0, CharacterPool.Num() - 1);
}

Pooling::Pooling()
{
}

Pooling::~Pooling()
{
}
