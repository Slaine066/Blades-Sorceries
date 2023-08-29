// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controllers/Hero/PlayerControllerHero.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Components/Widgets/UserWidgetCustom.h"
#include "Components/Widgets/PlayerScreenInfoUI.h"
#include "Components/Widgets/ItemSelectionUI.h"
#include "Actors/GameStates/GameStateCustom.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

APlayerControllerHero::APlayerControllerHero()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidgetCustom>WBP_MainPlayScreen_C(TEXT("'/Game/Portfolio_0/UI/WBP_MainPlayScreen.WBP_MainPlayScreen_C'"));
	if (WBP_MainPlayScreen_C.Succeeded())
	{
		UUserWidget = WBP_MainPlayScreen_C.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidgetCustom>WBP_ItemSelectionSpace_C(TEXT("'/Game/Portfolio_0/UI/WBP_ItemSelectionSpace.WBP_ItemSelectionSpace_C'"));
	if (WBP_ItemSelectionSpace_C.Succeeded())
	{
		UItemSelectionWidget = WBP_ItemSelectionSpace_C.Class;
	}
}

void APlayerControllerHero::SetPlayerHpInfoToWidget(int iDamage)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetPlayerHpInfo(Hero->Get_Attributes_Ref());
}

void APlayerControllerHero::IncreasePlayerHpInfoToWidget()
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetPlayerHpInfo(Hero->Get_Attributes_Ref());
}

void APlayerControllerHero::SetPlayerExpInfoToWidget()
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetPlayerExpInfo(Hero->Get_Attributes_Ref());
}

void APlayerControllerHero::SetPlayerItemInventory(const TArray<class AItemBase*>& InventoryArray)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetItemInventoryInfo(InventoryArray);
}

void APlayerControllerHero::SetGameTimer(int Minutes, int Seconds)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetTimerInfo(Minutes, Seconds);

	SetStage(Minutes);
}

void APlayerControllerHero::SetMobCount(int MobCount)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetMobCountInfo(MobCount);
}

void APlayerControllerHero::SetStage(int Stage)
{
	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->SetStageInfo(Stage);
}

void APlayerControllerHero::SetItemSelectionItem(const TArray<struct FItemData>& ChoiceItemArray)
{
	Cast<UItemSelectionUI>(UUserItemSelectionWidget)->SwitchVisibility(true);
	Cast<UItemSelectionUI>(UUserItemSelectionWidget)->SetItemSelectionInfotoSlot(ChoiceItemArray);
}

void APlayerControllerHero::EndSwitchItemSelection()
{
	Cast<UItemSelectionUI>(UUserItemSelectionWidget)->SwitchVisibility(false);
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

	GameState = GetWorld()->GetGameState<AGameStateCustom>();

	Hero = Cast<ACharacterHero>(GetPawn());

	// Setup Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext, 0);

	UUserScreenInfoWidget = CreateWidget<UUserWidgetCustom>(this, UUserWidget);
	UUserScreenInfoWidget->AddToViewport();

	UUserItemSelectionWidget = CreateWidget<UUserWidgetCustom>(this, UItemSelectionWidget);
	Cast<UItemSelectionUI>(UUserItemSelectionWidget)->SwitchVisibility(false);
	UUserItemSelectionWidget->AddToViewport();

	Cast<UPlayerScreenInfoUI>(UUserScreenInfoWidget)->BindAttribute(Hero->Get_Attributes());

	Hero->OnHitDamage.AddDynamic(this, &APlayerControllerHero::SetPlayerHpInfoToWidget);
	Hero->OnIncreaseHealth.AddDynamic(this, &APlayerControllerHero::IncreasePlayerHpInfoToWidget);
	Hero->OnPickUpExp.AddDynamic(this, &APlayerControllerHero::SetPlayerExpInfoToWidget);
	Hero->OnPickUpItem.AddDynamic(this, &APlayerControllerHero::SetPlayerItemInventory);

	GameState->OnGetTime.AddDynamic(this, &APlayerControllerHero::SetGameTimer);
	GameState->OnGetMonsterCount.AddDynamic(this, &APlayerControllerHero::SetMobCount);

	Hero->OnLevelUpItemSelection.AddDynamic(this, &APlayerControllerHero::SetItemSelectionItem);
	Hero->OnLevelUpItemSelectionEnd.AddDynamic(this, &APlayerControllerHero::EndSwitchItemSelection);
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
