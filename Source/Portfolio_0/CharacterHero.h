// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "InputActionValue.h"
#include "CharacterHero.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PORTFOLIO_0_API ACharacterHero : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	ACharacterHero();

	/*
	* Methods Inherited
	*/
	virtual void Die() override;

	/*
	* Methods
	*/
	// AnimNotify
	void OnUnsheath();
	void OnSheath();
	void OnNormalAttackCombo();
	void OnSkillEnd();

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/*
	* Methods
	*/
	// Input Action Functions
	virtual void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Unsheath(const FInputActionValue& Value);
	void NormalAttack(const FInputActionValue& Value);
	virtual void Skill_1(const FInputActionValue& Value);
	virtual void Skill_2(const FInputActionValue& Value);
	virtual void Skill_3(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	void PauseGame(const FInputActionValue& Value);

	/*
	* Variables
	*/
	// Input Actions
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* UnsheathAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* NormalAttackAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* Skill_1_Action;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* Skill_2_Action;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* Skill_3_Action;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* DashAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* PauseAction;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

private:
	/*
	* Methods
	*/

	/*
	* Variables
	*/
	// Spring Arm & Camera
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	// Input Mapping Context
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;

	// Montages
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* UnsheathMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* SheathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* UnsheathAttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TArray<UAnimMontage*> NormalAttackMontages;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* Skill_1_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* Skill_2_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* Skill_3_Montage;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	bool IsComboActive;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	int ComboCounter;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	bool IsSkilling;
};