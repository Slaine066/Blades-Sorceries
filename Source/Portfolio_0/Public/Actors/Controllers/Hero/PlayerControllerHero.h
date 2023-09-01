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

	/*
	* Inherited Methods
	*/

	/*
	* Methods 
	*/

	/*
	* Variables
	*/

protected:
	/*
	* Inherited Methods
	*/
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	/*
	* Methods
	*/
	// Input Action Functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void NormalAttack();
	void Fly();
	void Pause();

	// Testing Input Action Functions
	void Unsheath();
	void LevelUp();
	void Choice1();
	void Choice2();
	void Choice3();

	/*
	* Variables
	*/
	
private:
	/*
	* Methods
	*/

	/*
	* Variables
	*/
	// Input Mapping Context
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;

	// Input Actions
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* LookAction;
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
	UInputAction* UnsheathAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* LevelUpAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* Choice1Action;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* Choice2Action;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* Choice3Action;

	class ACharacterHero* Hero;
};
