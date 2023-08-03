// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceCharacter.h"
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		if (Character->GetMovementComponent()->IsFalling())
			IsFalling = true;
		else
			IsFalling = false;

		if (Character->GetVelocity().Size() > 0.f)
			IsRunning = true;
		else
			IsRunning = false;
	}
}