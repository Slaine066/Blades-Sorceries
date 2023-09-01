// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controllers/Hero/PlayerControllerHero.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

APlayerControllerHero::APlayerControllerHero()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Move"));
	if (MoveActionAsset.Succeeded())
		MoveAction = MoveActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Look"));
	if (LookActionAsset.Succeeded())
		LookAction = LookActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Jump"));
	if (JumpActionAsset.Succeeded())
		JumpAction = JumpActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> NormalAttackActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_NormalAttack"));
	if (NormalAttackActionAsset.Succeeded())
		NormalAttackAction = NormalAttackActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> FlyActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Flying"));
	if (FlyActionAsset.Succeeded())
		FlyingAction = FlyActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> PauseActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_PauseGame"));
	if (PauseActionAsset.Succeeded())
		PauseAction = PauseActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> UnsheathActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Unsheath"));
	if (UnsheathActionAsset.Succeeded())
		UnsheathAction = UnsheathActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> LevelUpActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_LevelUp"));
	if (LevelUpActionAsset.Succeeded())
		LevelUpAction = LevelUpActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Choice1ActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Choice1"));
	if (Choice1ActionAsset.Succeeded())
		Choice1Action = Choice1ActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Choice2ActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Choice2"));
	if (Choice2ActionAsset.Succeeded())
		Choice2Action = Choice2ActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Choice3ActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Choice3"));
	if (Choice3ActionAsset.Succeeded())
		Choice3Action = Choice3ActionAsset.Object;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/IMC_Character"));
	if (InputMappingContextAsset.Succeeded())
		InputMappingContext = InputMappingContextAsset.Object;
}

void APlayerControllerHero::BeginPlay()
{
	Super::BeginPlay();

	Hero = Cast<ACharacterHero>(GetPawn());

	// Setup Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext, 0);
}

void APlayerControllerHero::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings.
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Move);
		// Looking
		/*EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Look);*/
		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Jump);
		// Stop Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerControllerHero::StopJumping);
		// Normal Attack
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::NormalAttack);
		// Flying
		EnhancedInputComponent->BindAction(FlyingAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Fly);
		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Pause);
		
		// Unsheath (Testing)
		EnhancedInputComponent->BindAction(UnsheathAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Unsheath);
		// Level Up (Testing)
		EnhancedInputComponent->BindAction(LevelUpAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::LevelUp);
		// Choice 1 (Testing)
		EnhancedInputComponent->BindAction(Choice1Action, ETriggerEvent::Triggered, this, &APlayerControllerHero::Choice1);
		// Choice 2 (Testing)
		EnhancedInputComponent->BindAction(Choice2Action, ETriggerEvent::Triggered, this, &APlayerControllerHero::Choice2);
		// Choice 3 (Testing)
		EnhancedInputComponent->BindAction(Choice3Action, ETriggerEvent::Triggered, this, &APlayerControllerHero::Choice3);
	}
}

void APlayerControllerHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerControllerHero::Jump()
{
	if (Hero)
		Hero->Jump();
}

void APlayerControllerHero::StopJumping()
{
	if (Hero)
		Hero->StopJumping();
}

void APlayerControllerHero::Move(const FInputActionValue& Value)
{
	if (Hero)
		Hero->Move(Value);
}

void APlayerControllerHero::Look(const FInputActionValue& Value)
{
	if (Hero)
		Hero->Look(Value);
}

void APlayerControllerHero::NormalAttack()
{
	if (Hero)
		Hero->NormalAttack();
}

void APlayerControllerHero::Fly()
{
	if (Hero)
		Hero->Fly();
}

void APlayerControllerHero::Pause()
{
	if (Hero)
		Hero->Pause();
}

void APlayerControllerHero::Unsheath()
{
	if (Hero)
		Hero->Unsheath();
}

void APlayerControllerHero::LevelUp()
{
	if (Hero)
		Hero->LevelUp();
}

void APlayerControllerHero::Choice1()
{
	if (Hero)
		Hero->Choice1();
}

void APlayerControllerHero::Choice2()
{
	if (Hero)
		Hero->Choice2();
}

void APlayerControllerHero::Choice3()
{
	if (Hero)
		Hero->Choice3();
}
