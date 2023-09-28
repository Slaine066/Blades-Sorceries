// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/AnimInstanceCharacter.h"
#include "Actors/Characters/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

UAnimInstanceCharacter::UAnimInstanceCharacter()
{
}

void UAnimInstanceCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckCharacter();
}

void UAnimInstanceCharacter::CheckCharacter()
{
	if (!Character)
	{
		APawn* Pawn = TryGetPawnOwner();

		if (Pawn)
			Character = Cast<ACharacterBase>(Pawn);
	}
}

void UAnimInstanceCharacter::UpdateAnimation()
{
	if (Character)
	{
		IsFalling = Character->GetMovementComponent()->IsFalling();
		
		FVector CurrentVelocity = Character->GetVelocity();
		FRotator CurrentRotation = Character->GetActorRotation();

		Speed = CurrentVelocity.SquaredLength();
		Direction = CalculateDirection(CurrentVelocity, CurrentRotation);
		
		IsRunning = Speed > 0.0f;

		GEngine->AddOnScreenDebugMessage(111, 999.f, FColor::Blue, FString::Printf(TEXT("Speed: %f"), Speed));
		GEngine->AddOnScreenDebugMessage(222, 999.f, FColor::Blue, FString::Printf(TEXT("Direction: %f"), Direction));
	}
}

void UAnimInstanceCharacter::Die()
{
	CheckCharacter();

	if (Character)
	{
		Character->GetMesh()->bPauseAnims = true;
		Character->GetMesh()->bNoSkeletonUpdate = true;
		
		// Remove Collisions
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	}
}