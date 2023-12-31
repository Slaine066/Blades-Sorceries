// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controllers/Hero/PlayerControllerHero.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerScreenInfoUI.h"
#include "Components/Widgets/ItemSelection/ItemSelectionUI.h"
#include "Components/Widgets/PauseMenu/PauseMenuUI.h"
#include "Components/Widgets/ClassSelection/ClassSelectionUI.h"
#include "Actors/GameStates/GameStateCustom.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Actors/Characters/Hero/HeroMage.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Engine/Classes/Kismet/KismetMathLibrary.h>

APlayerControllerHero::APlayerControllerHero()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Actions */
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Move"));
	if (MoveActionAsset.Succeeded())
		MoveAction = MoveActionAsset.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_Jump"));
	if (JumpActionAsset.Succeeded())
		JumpAction = JumpActionAsset.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> NormalAttackActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_NormalAttack"));
	if (NormalAttackActionAsset.Succeeded())
		NormalAttackAction = NormalAttackActionAsset.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> PauseActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_PauseGame"));
	if (PauseActionAsset.Succeeded())
		PauseAction = PauseActionAsset.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> LevelUpActionAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/Actions/IA_LevelUp"));
	if (LevelUpActionAsset.Succeeded())
		LevelUpAction = LevelUpActionAsset.Object;

	/* Input Mapping Context */
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextAsset(TEXT("/Game/Portfolio_0/Characters/Hero/Inputs/IMC_Character"));
	if (InputMappingContextAsset.Succeeded())
		InputMappingContext = InputMappingContextAsset.Object;

	/* Widgets */
	static ConstructorHelpers::FClassFinder<UUserWidgetCustom>WBP_MainPlayScreen_C(TEXT("'/Game/Portfolio_0/UI/WBP_MainPlayScreen.WBP_MainPlayScreen_C'"));
	if (WBP_MainPlayScreen_C.Succeeded())
		UUserWidget = WBP_MainPlayScreen_C.Class;
	static ConstructorHelpers::FClassFinder<UUserWidgetCustom>WBP_ItemSelectionSpace_C(TEXT("'/Game/Portfolio_0/UI/WBP_ItemSelectionSpace.WBP_ItemSelectionSpace_C'"));
	if (WBP_ItemSelectionSpace_C.Succeeded())
		UItemSelectionWidget = WBP_ItemSelectionSpace_C.Class;
	static ConstructorHelpers::FClassFinder<UUserWidgetCustom>WBP_ClassSelection_C(TEXT("'/Game/Portfolio_0/UI/WBP_ClassSelection.WBP_ClassSelection_C'"));
	if (WBP_ClassSelection_C.Succeeded())
		ClassSelectionWidget = WBP_ClassSelection_C.Class;
	static ConstructorHelpers::FClassFinder<UUserWidgetCustom>WBP_PauseMenu_C(TEXT("'/Game/Portfolio_0/UI/WBP_PauseMenu.WBP_PauseMenu_C'"));
	if (WBP_PauseMenu_C.Succeeded())
		PauseMenuWidget = WBP_PauseMenu_C.Class;
}

void APlayerControllerHero::SetPlayerHpInfoToWidget(int iDamage)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetPlayerHpInfo(Hero->Get_Attributes());
}

void APlayerControllerHero::IncreasePlayerHpInfoToWidget()
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetPlayerHpInfo(Hero->Get_Attributes());
}

void APlayerControllerHero::SetPlayerExpInfoToWidget()
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetPlayerExpInfo(Hero->Get_Attributes());
}

void APlayerControllerHero::SetPlayerItemInventory(const TArray<class AItemBase*>& InventoryArray)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetItemInventoryInfo(InventoryArray);
}

void APlayerControllerHero::SetGameTimer(int Minutes, int Seconds)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetTimerInfo(Minutes, Seconds);
}

void APlayerControllerHero::SetItemSelectionItem(const TArray<struct FItemData>& ChoiceItemArray)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetPlayerLevelInfo(Hero->Get_Attributes());
	
	// ItemSelectionUI
	if (!UUserItemSelectionWidget)
		UUserItemSelectionWidget = CreateWidget<UUserWidgetCustom>(this, UItemSelectionWidget);

	UUserItemSelectionWidget->AddToViewport();

	Cast<UItemSelectionUI>(UUserItemSelectionWidget)->SetItemSelectionInfotoSlot(ChoiceItemArray);
}

void APlayerControllerHero::EndSwitchItemSelection()
{
	Cast<UItemSelectionUI>(UUserItemSelectionWidget)->RemoveFromViewport();
}

void APlayerControllerHero::ClassSelection()
{
	if (!IsPaused())
	{
		SetPause(true);

		// Add PauseMenu UI to Viewport
		if (!ClassSelectionUI)
			ClassSelectionUI = CreateWidget<UClassSelectionUI>(GetWorld(), ClassSelectionWidget);
		
		ClassSelectionUI->AddToViewport();
	}
}

void APlayerControllerHero::EndClassSelection()
{
	ClassSelectionUI->RemoveFromViewport();

	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->InitSkills(Hero->Get_Skills());
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->ShowSkillBar();
}

void APlayerControllerHero::LookAtCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);

	if (Hit.bBlockingHit)
	{
		FVector CursorHitLocation = FVector(Hit.Location.X, Hit.Location.Y, Hero->GetActorLocation().Z);

		LookDirection = UKismetMathLibrary::FindLookAtRotation(Hero->GetActorLocation(), CursorHitLocation);
		Hero->SetActorRotation(LookDirection);
	}
}

UUserWidgetCustom* APlayerControllerHero::GetUserWidget() const
{
	return UUserScreenInfoWidget;
}

UUserWidgetCustom* APlayerControllerHero::GetItemSelectionWidget() const
{
	return UUserItemSelectionWidget;	
}

void APlayerControllerHero::BeginPlay()
{
	Super::BeginPlay();

	Hero = Cast<ACharacterHero>(GetPawn());
	GameState = GetWorld()->GetGameState<AGameStateCustom>();

	// Setup Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext, 0);

	// PlayerScreenInfoUI
	UUserScreenInfoWidget = CreateWidget<UUserWidgetCustom>(this, UUserWidget);
	UUserScreenInfoWidget->AddToViewport();
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->InitAttributes(Hero->Get_Attributes());

	// Delegates Bindings
	Hero->OnHitDamage.AddDynamic(this, &APlayerControllerHero::SetPlayerHpInfoToWidget);
	Hero->OnIncreaseHealth.AddDynamic(this, &APlayerControllerHero::IncreasePlayerHpInfoToWidget);
	Hero->OnPickUpExp.AddDynamic(this, &APlayerControllerHero::SetPlayerExpInfoToWidget);
	Hero->OnPickUpItem.AddDynamic(this, &APlayerControllerHero::SetPlayerItemInventory);

	Hero->OnLevelUpItemSelection.AddDynamic(this, &APlayerControllerHero::SetItemSelectionItem);
	Hero->OnLevelUpItemSelectionEnd.AddDynamic(this, &APlayerControllerHero::EndSwitchItemSelection);
	Hero->OnLevelUpClassSelection.AddDynamic(this, &APlayerControllerHero::ClassSelection);
	Hero->OnLevelUpClassSelectionEnd.AddDynamic(this, &APlayerControllerHero::EndClassSelection);

	GameState->OnGetTime.AddDynamic(this, &APlayerControllerHero::SetGameTimer);
}

void APlayerControllerHero::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings.
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Move);
		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Jump);
		// Stop Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerControllerHero::StopJumping);
		// Normal Attack
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Attack);
		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::Pause);
		
		// Level Up (Testing)
		EnhancedInputComponent->BindAction(LevelUpAction, ETriggerEvent::Triggered, this, &APlayerControllerHero::LevelUp);
	}
}

void APlayerControllerHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Character's Look Direction is always towards the mouse cursor. */
	LookAtCursor();
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

void APlayerControllerHero::Attack()
{
	if (Hero)
		Hero->Attack();
}

void APlayerControllerHero::Pause()
{
	if (!IsPaused())
	{
		// Add PauseMenu UI to Viewport
		if (!PauseMenuUI)
			PauseMenuUI = CreateWidget<UPauseMenuUI>(GetWorld(), PauseMenuWidget);
			
		PauseMenuUI->AddToViewport();

		SetPause(true);
	}
}

void APlayerControllerHero::LevelUp()
{
	if (Hero)
		Hero->LevelUp();
}