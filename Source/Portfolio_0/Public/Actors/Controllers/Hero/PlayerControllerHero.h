// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PlayerControllerHero.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API APlayerControllerHero : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerControllerHero();

	/* Inherited Methods */
	virtual void SetupInputComponent() override;

	/* Methods */
	UFUNCTION()
	void SetPlayerHpInfoToWidget(int iDamage);
	UFUNCTION()
	void IncreasePlayerHpInfoToWidget();
	UFUNCTION()
	void SetPlayerExpInfoToWidget();
	UFUNCTION()
	void SetPlayerItemInventory(const TArray<class AItemBase*>& InventoryArray);
	UFUNCTION()
	void SetGameTimer(int Minutes, int Seconds);
	UFUNCTION()
	void SetMobCount(int MobCount);
	UFUNCTION()
	void SetStage(int Stage);

	UFUNCTION()
	void SetItemSelectionItem(const TArray<struct FItemData>& ChoiceItemArray);
	UFUNCTION()
	void EndSwitchItemSelection();

	/* Variables */
	class UUserWidgetCustom* GetUserWidget() const;
	class UUserWidgetCustom* GetItemSelectionWidget() const;

protected:
	/* Inherited Methods */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Methods */
	// Input Action Functions
	void Move(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void NormalAttack();
	void Fly();
	void Pause();

	// Testing Input Action Functions
	void LevelUp();

	UFUNCTION()
	void ClassSelection();
	UFUNCTION()
	void EndClassSelection();

	/* Variables */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidgetCustom> UUserWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidgetCustom> UItemSelectionWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidgetCustom> ClassSelectionWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidgetCustom> PauseMenuWidget;

private:
	/* Methods */

	/* Variables */
	// Input Mapping Context
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;

	// Input Actions
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* NormalAttackAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* FlyingAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* PauseAction;

	// Testing Input Actions
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* LevelUpAction;

	UPROPERTY()
	class UUserWidgetCustom* UUserScreenInfoWidget = nullptr;
	UPROPERTY()
	class UUserWidgetCustom* UUserItemSelectionWidget = nullptr;
	UPROPERTY()
	class UClassSelectionUI* ClassSelectionUI = nullptr;
	UPROPERTY()
	class UPauseMenuUI* PauseMenuUI = nullptr;

	class ACharacterHero* Hero;
	class AGameStateCustom* GameState;
};
