// Copyright Epic Games, Inc. All Rights Reserved.

#include "VampireSurvivalCharacter.h"
#include "VampireSurvivalProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AVampireSurvivalCharacter

AVampireSurvivalCharacter::AVampireSurvivalCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AVampireSurvivalCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AVampireSurvivalCharacter::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);
	//for (AActor* Enemy : Enemies)
	//{
	//	if (IsEnemyInView(Enemy))
	//	{
	//		// Carica il nemico
	//		// Ad esempio, attiva il rendering o l'intelligenza artificiale
	//	}
	//	else
	//	{
	//		// Scarica il nemico
	//		// Ad esempio, disattiva il rendering o l'intelligenza artificiale
	//	}
	//}
}

//////////////////////////////////////////////////////////////////////////// Input

void AVampireSurvivalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVampireSurvivalCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVampireSurvivalCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

//Move to CullingSystem
//bool AVampireSurvivalCharacter::IsEnemyInView(AActor* Enemy)
//{
//	//Player location and forward
//	FVector PlayerLocation = GetActorForwardVector();
//	FVector ForwardVector = GetActorForwardVector();
//
//	//Enemy location and forward
//	FVector EnemyLocation = Enemy->GetActorLocation();
//	FVector DirectionToEnemy = (EnemyLocation - PlayerLocation).GetSafeNormal();
//
//	//View angle
//	float Angle = FMath::Acos(FVector::DotProduct(ForwardVector, DirectionToEnemy));
//	Angle = FMath::RadiansToDegrees(Angle);
//
//	//Distance from Player
//	float Distance = FVector::Dist(PlayerLocation, EnemyLocation);
//
//	//return true if in range, return false is not
//	return (Angle <= ViewAngle && Distance <= ViewDistance);
//}

void AVampireSurvivalCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AVampireSurvivalCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}