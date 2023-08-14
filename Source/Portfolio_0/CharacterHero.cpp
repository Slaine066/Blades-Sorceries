// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHero.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "AnimInstanceHero.h"
#include "WeaponBase.h"

ACharacterHero::ACharacterHero() 
	: IsComboActive(false), ComboCounter(0)
{
	// Character
	// Doesn't rotate when Camera rotates.
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// MovementComponent
	// Moves in the direction of the input at "RotationRate" speed.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 650.f;

	// SpringArmComponent
	// Enable the Pawn to control Camera rotation.
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 100.f);
	SpringArmComponent->bUsePawnControlRotation = true;

	// CameraComponent
	// Attach the "CameraComponent" to the "SprintArmComponent".
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ACharacterHero::BeginPlay()
{
	Super::BeginPlay();

	// Setup Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(InputMappingContext, 0);

	// Setup Collision Profile
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Hero"));

	// Spawn Weapon at run-time.
	if (WeaponClassLeft)
	{
		WeaponLeft = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassLeft);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocketSheath");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponLeft, GetMesh());
			WeaponLeft->SetOwner(this);

			// Setup Collision Profile
			WeaponLeft->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponHero"));
		}
	}
}

void ACharacterHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings.
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacterHero::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacterHero::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterHero::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterHero::Look);

		// Unsheath
		EnhancedInputComponent->BindAction(UnsheathAction, ETriggerEvent::Triggered, this, &ACharacterHero::Unsheath);

		// Normal Attack
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Triggered, this, &ACharacterHero::NormalAttack);

		// Skills
		EnhancedInputComponent->BindAction(Skill_1_Action, ETriggerEvent::Triggered, this, &ACharacterHero::Skill_1);
		EnhancedInputComponent->BindAction(Skill_2_Action, ETriggerEvent::Triggered, this, &ACharacterHero::Skill_2);
		EnhancedInputComponent->BindAction(Skill_3_Action, ETriggerEvent::Triggered, this, &ACharacterHero::Skill_3);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ACharacterHero::Dash);

		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ACharacterHero::PauseGame);
	}
}

void ACharacterHero::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	// Logging
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hero Takes Damage: %f."), Damage));
}

void ACharacterHero::Die()
{
	Super::Die();

	// Disable Inputs
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
		DisableInput(PlayerController);
}

void ACharacterHero::Move(const FInputActionValue& Value)
{
	// Can't move while using Skills.
	if (IsSkilling || IsHit)
		return;

	// Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get Forward Vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Get Right Vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add Movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterHero::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to Controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacterHero::Unsheath(const FInputActionValue& Value)
{
	// Can't Unsheath/Sheath while using Normal Attacks or Skills.
	if (IsAttacking || IsSkilling || IsHit)
		return;

	UAnimInstanceHero* AnimInstanceHero = Cast<UAnimInstanceHero>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHero)
		return;

	if (AnimInstanceHero->IsWeaponUnsheathed)
		PlayAnimMontage(SheathMontage);
	else
		PlayAnimMontage(UnsheathMontage);
}

void ACharacterHero::NormalAttack(const FInputActionValue& Value)
{
	// Can't use Normal Attacks while Skilling.
	if (IsSkilling || IsHit)
		return;

	// If already Attacking, toggle Combo variable.
	if (IsAttacking)
	{
		if (ComboCounter != 0)
			IsComboActive = true;
	}
	else
	{
		UAnimInstanceHero* AnimInstanceHero = Cast<UAnimInstanceHero>(GetMesh()->GetAnimInstance());
		if (!AnimInstanceHero)
			return;

		if (AnimInstanceHero->IsWeaponUnsheathed)
			PlayAnimMontage(NormalAttackMontages[0]);
		else
		{
			PlayAnimMontage(UnsheathAttackMontage);
		}

		IsAttacking = true;
		ComboCounter = 1;
	}
}

void ACharacterHero::Skill_1(const FInputActionValue& Value)
{
	// Can't use Skills when Skilling.
	if (IsSkilling || IsHit)
		return;

	UAnimInstanceHero* AnimInstanceHero = Cast<UAnimInstanceHero>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHero)
		return;

	// Can't use Skills when Jumping.
	if (AnimInstanceHero->IsFalling)
		return;

	// Can't use Skills when Weapon is Sheathed.
	if (!AnimInstanceHero->IsWeaponUnsheathed)
		return;

	PlayAnimMontage(Skill_1_Montage);
	IsSkilling = true;
	IsAttacking = false;
}

void ACharacterHero::Skill_2(const FInputActionValue& Value)
{
	// Can't use Skills when Skilling.
	if (IsSkilling || IsHit)
		return;

	UAnimInstanceHero* AnimInstanceHero = Cast<UAnimInstanceHero>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHero)
		return;

	// Can't use Skills when Jumping.
	if (AnimInstanceHero->IsFalling)
		return;

	// Can't use Skills when Weapon is Sheathed.
	if (!AnimInstanceHero->IsWeaponUnsheathed)
		return;

	PlayAnimMontage(Skill_2_Montage);
	IsSkilling = true;
	IsAttacking = false;
}

void ACharacterHero::Skill_3(const FInputActionValue& Value)
{
	// Can't use Skills when Skilling.
	if (IsSkilling || IsHit)
		return;

	UAnimInstanceHero* AnimInstanceHero = Cast<UAnimInstanceHero>(GetMesh()->GetAnimInstance());
	if (!AnimInstanceHero)
		return;

	// Can't use Skills when Jumping.
	if (AnimInstanceHero->IsFalling)
		return;

	// Can't use Skills when Weapon is Sheathed.
	if (!AnimInstanceHero->IsWeaponUnsheathed)
		return;

	PlayAnimMontage(Skill_3_Montage);
	IsSkilling = true;
	IsAttacking = false;
}

void ACharacterHero::Dash(const FInputActionValue& Value)
{
}

void ACharacterHero::PauseGame(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (PlayerController->IsPaused())
			PlayerController->SetPause(false);
		else
			PlayerController->SetPause(true);
	}
}

void ACharacterHero::OnUnsheath()
{
	// Retrieve WeaponSocket.
	if (const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocket"))
	{
		// Attach Weapon to WeaponSocket and set Owner.
		WeaponSocket->AttachActor(WeaponLeft, GetMesh());
		WeaponLeft->SetOwner(this);
	}
}

void ACharacterHero::OnSheath()
{
	// Retrieve WeaponSocketSheath.
	if (const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocketSheath"))
	{
		// Attach Weapon to WeaponSocket and set Owner.
		WeaponSocket->AttachActor(WeaponLeft, GetMesh());
		WeaponLeft->SetOwner(this);
	}
}

void ACharacterHero::OnNormalAttackCombo()
{
	if (IsComboActive)
	{
		IsComboActive = false;

		switch (ComboCounter)
		{
		case 1:
			ComboCounter = 2;
			PlayAnimMontage(NormalAttackMontages[1]);
			break;
		case 2:
			ComboCounter = 3;
			PlayAnimMontage(NormalAttackMontages[2]);
			break;
		case 3:
			ComboCounter = 0;
			PlayAnimMontage(NormalAttackMontages[3]);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("ACharacterHero::OnNormalAttackCombo(): Default"));
		}
	}
	else
	{
		IsAttacking = false;
		ComboCounter = 0;
	}
}

void ACharacterHero::OnSkillEnd()
{
	IsSkilling = false;
}