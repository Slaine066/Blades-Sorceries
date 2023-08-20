// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHero.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "AnimInstanceHero.h"
#include "WeaponBase.h"
#include "Engine/DataTable.h"
#include "ItemBase.h"
#include "Pickupable.h"
#include "Utility.h"

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
	SpringArmComponent->TargetArmLength = 1000.f;
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArmComponent->bUsePawnControlRotation = true;	

	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagMaxDistance = 100000.f;
	SpringArmComponent->CameraLagSpeed = 5.f;
	SpringArmComponent->bDoCollisionTest = false;

	// CameraComponent
	// Attach the "CameraComponent" to the "SprintArmComponent".
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	FTransform AddCamOffset;	
	AddCamOffset.SetLocation(FVector(200.f, 0.f, 600.f));
	AddCamOffset.SetRotation(FRotator(-45.f, 0.f, 0.f).Quaternion());	

	CameraComponent->AddAdditiveOffset(AddCamOffset, 10.f);
	
	// SphereCollisionComponent
	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollisionComponent->InitSphereRadius(200.f);
	SphereCollisionComponent->SetupAttachment(RootComponent);
}

void ACharacterHero::BeginPlay()
{
	Super::BeginPlay();

	// Setup Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(InputMappingContext, 0);

	// Setup Collision Profiles
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Hero"));
	SphereCollisionComponent->SetCollisionProfileName(TEXT("PickupSphere"));

	// Overlap Delegates
	SphereCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACharacterHero::OnSphereOverlapBegin);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacterHero::OnCapsuleOverlapBegin);
	
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

	Log();
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
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterHero::Look);

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
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ACharacterHero::Pause);

		// Level Up (Testing)
		EnhancedInputComponent->BindAction(LevelUpAction, ETriggerEvent::Triggered, this, &ACharacterHero::LevelUp);
		// Choice 1 (Testing)
		EnhancedInputComponent->BindAction(Choice1Action, ETriggerEvent::Triggered, this, &ACharacterHero::Choice1);
		// Choice 2 (Testing)
		EnhancedInputComponent->BindAction(Choice2Action, ETriggerEvent::Triggered, this, &ACharacterHero::Choice2);
		// Choice 3 (Testing)
		EnhancedInputComponent->BindAction(Choice3Action, ETriggerEvent::Triggered, this, &ACharacterHero::Choice3);
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

void ACharacterHero::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnMontageEnded(Montage, bInterrupted);
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

void ACharacterHero::Pause(const FInputActionValue& Value)
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

void ACharacterHero::GainExperience(int Amount)
{
	Attributes.Experience += Amount;

	if (Attributes.Experience >= Attributes.ExperienceMax)
		LevelUp();

	TriggerPickupExpEvent();
}

void ACharacterHero::IncreaseHealth(int Amount)
{
	Attributes.Health += Amount;

	if (Attributes.Health >= Attributes.HealthMax)
		Attributes.Health = Attributes.HealthMax;
}

void ACharacterHero::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APickupable* Pickupable = Cast<APickupable>(OtherActor);
	if (!Pickupable)
		return;

	switch (Pickupable->Get_Type())
	{
		case EPickupableType::EXPERIENCE_SMALL:
		case EPickupableType::EXPERIENCE_MEDIUM:
		case EPickupableType::EXPERIENCE_BIG:
		{
			Pickupable->Set_Hero(this);
			break;
		}
	}	
}

void ACharacterHero::OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APickupable* Pickupable = Cast<APickupable>(OtherActor);
	if (!Pickupable)
		return;

	switch (Pickupable->Get_Type())
	{
	case EPickupableType::EXPERIENCE_SMALL:
	case EPickupableType::EXPERIENCE_MEDIUM:
	case EPickupableType::EXPERIENCE_BIG:
		GainExperience(Pickupable->Get_GivenExperience());
		break;
	case EPickupableType::POTION:
		IncreaseHealth(Pickupable->Get_GivenHealth());
		break;
	case EPickupableType::CHEST:
		GenerateChoices();
		break;
	}

	Pickupable->Destroy();
}

void ACharacterHero::LevelUp()
{
	Attributes.Level += 1;
	Attributes.Experience = 0;
	Attributes.ExperienceMax *= 1.25f;

	GenerateChoices();
}

void ACharacterHero::GenerateChoices()
{
	/* Pause Game */
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
		PlayerController->SetPause(true);

		/* Get Choosable Items */
	TArray<FItemData*> AllItems;
	ItemsDataTable->GetAllRows("", AllItems);

	TArray<FItemData> ChoosableItems; // If have "Attack Speed Boost (Common), the ChoosableItem will be "Attack Boost (Uncommon).

	if (Items.IsEmpty())
	{
		/* Filter Choosable Items (EItemGrade::COMMON Items). */
		for (FItemData* Row : AllItems)
		{
			if (Row->Grade == EItemGrade::COMMON)
				ChoosableItems.Add(*Row);
		}
	}
	else
	{
		for (FItemData* Row : AllItems)
		{
			auto Predicate = [&](AItemBase* ItemPtr) { 
				return ItemPtr && ItemPtr->Get_ItemData().Item == Row->Item; 
			};

			AItemBase** Item = Items.FindByPredicate(Predicate);
			if (Item)
			{
				/* Check Grade */
				EItemGrade CurrentGrade = (*Item)->Get_ItemData().Grade;
				if (CurrentGrade == EItemGrade::LEGENDARY)
					continue;

				if (Row->Grade == (EItemGrade)((int)CurrentGrade + 1))
					ChoosableItems.Add(*Row);
			}
			else
			{
				if (Row->Grade == EItemGrade::COMMON)
					ChoosableItems.Add(*Row);
			}
		}
	}

	/* Shuffle ChoosableItems */
	ChoosableItems.Sort([](const FItemData& A, const FItemData& B) {
		return FMath::RandBool(); // Sort with random order, effectively shuffling the array
		});

	/* Keep first 3 Elements. */
	Choices.Empty();
	Choices.Add(ChoosableItems[0]);
	Choices.Add(ChoosableItems[1]);
	Choices.Add(ChoosableItems[2]);

	/*
	* Log Item Choices
	*/
	if (!Choices.IsEmpty())
	{
		// Log Choice 1
		GEngine->AddOnScreenDebugMessage((int)ELOG::ITEM_CHOICE_1, 999.f, FColor::Blue, FString::Printf(TEXT("1. First Choice: %s"), *Choices[0].Name.ToString()), false);
		// Log Choice 2
		GEngine->AddOnScreenDebugMessage((int)ELOG::ITEM_CHOICE_2, 999.f, FColor::Blue, FString::Printf(TEXT("2. Second Choice: %s"), *Choices[1].Name.ToString()), false);
		// Log Choice 3
		GEngine->AddOnScreenDebugMessage((int)ELOG::ITEM_CHOICE_3, 999.f, FColor::Blue, FString::Printf(TEXT("3. Third Choice: %s"), *Choices[2].Name.ToString()), false);
	}
}

/*
* Should be able to have not more than:
* - 6 EItemType::ATTRIBUTE_BOOST Items;
* - 6 EItemType::ABILITY Items.
*/
void ACharacterHero::CheckChoices()
{
	// TODO
}

void ACharacterHero::Choice1()
{
	/* Create Item based on Chosen Item. */
	AItemBase* Item = NewObject<AItemBase>();
	Item->Set_ItemData(Choices[0]);
	
	/* Empty Choices Array. */
	Choices.Empty();
	
	AddItem(Item);
}

void ACharacterHero::Choice2()
{
	/* Create Item based on Chosen Item. */
	AItemBase* Item = NewObject<AItemBase>();
	Item->Set_ItemData(Choices[1]);

	/* Empty Choices Array. */
	Choices.Empty();

	AddItem(Item);
}

void ACharacterHero::Choice3()
{
	/* Create Item based on Chosen Item. */
	AItemBase* Item = NewObject<AItemBase>();
	Item->Set_ItemData(Choices[2]);

	/* Empty Choices Array. */
	Choices.Empty();

	AddItem(Item);
}

void ACharacterHero::AddItem(AItemBase* Item)
{
	auto Predicate = [&](AItemBase* ItemPtr) {
		return ItemPtr && ItemPtr->Get_ItemData().Item == Item->Get_ItemData().Item;
	};

	AItemBase** CurrentItem = Items.FindByPredicate(Predicate);
	if (CurrentItem)
	{
		/* Replace Item */
		int Index = Items.IndexOfByPredicate(Predicate);

		if (Items.IsValidIndex(Index))
		{
			Items[Index] = Item;
			Item->Initialize(this);
		}
	}
	else
	{
		/* Add Item to Items Array. */
		Items.Add(Item);
		Item->Initialize(this);
	}

	TriggerPickupItemEvent(Items);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
		PlayerController->SetPause(false);
}

void ACharacterHero::Log()
{
	/*
	* Log Attributes
	*/
	GEngine->AddOnScreenDebugMessage((int)ELOG::ATTRIBUTES, 999.f, FColor::Green, TEXT("Attributes"), false);
	// Log Level
	GEngine->AddOnScreenDebugMessage((int)ELOG::LEVEL, 999.f, FColor::Emerald, FString::Printf(TEXT("Level: %d"), Attributes.Level), false);
	// Log ExperienceMax
	GEngine->AddOnScreenDebugMessage((int)ELOG::EXPERIENCE_MAX, 999.f, FColor::Emerald, FString::Printf(TEXT("Experience Max: %d"), Attributes.ExperienceMax), false);
	// Log Experience
	GEngine->AddOnScreenDebugMessage((int)ELOG::EXPERIENCE, 999.f, FColor::Emerald, FString::Printf(TEXT("Experience: %d"), Attributes.Experience), false);
	// Log HealthMax
	GEngine->AddOnScreenDebugMessage((int)ELOG::HEALTH_MAX, 999.f, FColor::Emerald, FString::Printf(TEXT("Health Max: %d"), Attributes.HealthMax), false);
	// Log Health
	GEngine->AddOnScreenDebugMessage((int)ELOG::HEALTH, 999.f, FColor::Emerald, FString::Printf(TEXT("Health: %d"), Attributes.Health), false);
	// Log HealthRegen
	GEngine->AddOnScreenDebugMessage((int)ELOG::HEALTH_REGEN, 999.f, FColor::Emerald, FString::Printf(TEXT("Health Regen: %f"), Attributes.HealthRegen), false);
	// Log Damage
	GEngine->AddOnScreenDebugMessage((int)ELOG::DAMAGE, 999.f, FColor::Emerald, FString::Printf(TEXT("Damage: %d"), Attributes.Damage), false);
	// Log AttackSpeed
	GEngine->AddOnScreenDebugMessage((int)ELOG::ATTACK_SPEED, 999.f, FColor::Emerald, FString::Printf(TEXT("Attack Speed: %f"), Attributes.AttackSpeed), false);
	// Log Armor
	GEngine->AddOnScreenDebugMessage((int)ELOG::ARMOR, 999.f, FColor::Emerald, FString::Printf(TEXT("Armor: %f"), Attributes.Armor), false);
	// Log MovementSpeed
	GEngine->AddOnScreenDebugMessage((int)ELOG::MOVEMENT_SPEED, 999.f, FColor::Emerald, FString::Printf(TEXT("Movement Speed: %f"), Attributes.MovementSpeed), false);
	// Log PickupRange
	GEngine->AddOnScreenDebugMessage((int)ELOG::PICKUP_RANGE, 999.f, FColor::Emerald, FString::Printf(TEXT("Pickup Range: %f"), Attributes.PickupRange), false);
	// Log CooldownReduction
	GEngine->AddOnScreenDebugMessage((int)ELOG::COOLDOWN_REDUCTION, 999.f, FColor::Emerald, FString::Printf(TEXT("Cooldown Reduction: %f"), Attributes.CooldownReduction), false);

	/*
	* Log Items
	*/
	if (!Items.IsEmpty())
	{
		FString ItemsString;
		for (int i = 0; i < Items.Num(); i++)
		{
			FString Index = FString::Printf(TEXT("%i. "), i + 1);
			ItemsString.Append(Index);
			ItemsString.Append(*Items[i]->Get_ItemData().Name.ToString());
			ItemsString.Append(" ");
		}

		GEngine->AddOnScreenDebugMessage((int)ELOG::ITEMS, 999.f, FColor::Magenta, ItemsString, false);
	}

	/*
	* Remove Log Choices
	*/
	GEngine->RemoveOnScreenDebugMessage((int)ELOG::ITEM_CHOICE_1);
	GEngine->RemoveOnScreenDebugMessage((int)ELOG::ITEM_CHOICE_2);
	GEngine->RemoveOnScreenDebugMessage((int)ELOG::ITEM_CHOICE_3);
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

void ACharacterHero::TriggerPickupItemEvent(const TArray<class AItemBase*>& InventoryArray)
{
	OnPickUpItem.Broadcast(InventoryArray);
}

void ACharacterHero::TriggerPickupExpEvent()
{
	OnPickUpExp.Broadcast();
}
