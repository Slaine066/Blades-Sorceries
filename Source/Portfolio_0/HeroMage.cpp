// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroMage.h"
#include <EnhancedInputComponent.h>
#include "AnimInstanceHeroMage.h"

AHeroMage::AHeroMage()
	:IsFlyingState(false), IsSpellState(false)
{
}

void AHeroMage::OnFlying()
{
	IsFlyingState = true;
}

void AHeroMage::OnLanding()
{
	IsFlyingState = false;
}

void AHeroMage::OnNormalAttackSpell()
{
	//Add Need Attack Code

	IsSpellState = true;
}

void AHeroMage::OnSpellEnd()
{
	IsSpellState = false;
}

void AHeroMage::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroMage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroMage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Flying
		EnhancedInputComponent->BindAction(FlyingAction, ETriggerEvent::Triggered, this, &AHeroMage::Flying);

		// NormalAttackSpell
		EnhancedInputComponent->BindAction(NormalAttackSpellAction, ETriggerEvent::Triggered, this, &AHeroMage::NormalAttackSpell);
		
	}
}

void AHeroMage::Flying(const FInputActionValue& Value)
{
	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (AnimInstanceHeroMage->IsFlying)
	{
		PlayAnimMontage(Landing_Montage);
	}
	else
	{
		PlayAnimMontage(Flying_Montage);
	}
}

void AHeroMage::NormalAttackSpell(const FInputActionValue& Value)
{
	UAnimInstanceHeroMage* AnimInstanceHeroMage = Cast<UAnimInstanceHeroMage>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHeroMage)
	{
		return;
	}

	if (AnimInstanceHeroMage->IsFlying)
	{
		PlayAnimMontage(NormalAttackSpell_Fly_Montage);
	}
	else
	{
		PlayAnimMontage(NormalAttackSpell_Montage);
	}
}
