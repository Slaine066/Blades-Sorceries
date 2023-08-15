// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHero.h"
#include "HeroMage.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API AHeroMage : public ACharacterHero
{
	GENERATED_BODY()
	
public:
	AHeroMage();

	/* Methods */
	void OnFlying();
	void OnLanding();
	void OnNormalAttackSpell();
	void OnSpellEnd();
	void OnAimEnd();
	void OnHitable();

	/* Variables */
	// Magic muzzle offset from the camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		FVector SpellMuzzleOffset;

protected:
	/* Methods Inherited */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/* Methods */
	void Flying(const FInputActionValue& Value);
	void NormalAttackSpell(const FInputActionValue& Value);

	UFUNCTION()
	void NormalAttackFire();

	virtual void Move(const FInputActionValue& Value);
	//RangeAttackSpell
	virtual void Skill_1(const FInputActionValue& Value);
	//PirecingAttackSpell
	virtual void Skill_2(const FInputActionValue& Value);
	//ChargeAttackSpell
	virtual void Skill_3(const FInputActionValue& Value);

	/* Variables */

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* FlyingAction;
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* NormalAttackSpellAction;

	//projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectileBase> ProjectileClass;



private:
	/* Methods */

	UPROPERTY(EditDefaultsOnly, Category = "Flying")
		UAnimMontage* Flying_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Flying")
		UAnimMontage* Landing_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* NormalAttackSpell_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* NormalAttackSpell_Fly_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* RangeAttackSpell_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* RangeAttackSpell_Fly_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* PirecingAttackSpell_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* PirecingAttackSpell_Fly_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* ChargeAttackSpell_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Spell")
		UAnimMontage* ChargeAttackSpell_Fly_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		UAnimMontage* HitMotion_Montage;
	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		UAnimMontage* HitMotion_Fly_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* HitMontage_Fly;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* DeathMontage_Fly;
	/* Variables */

	UPROPERTY(VisibleAnywhere, Category = "Flying")
		bool IsFlyingState;
	UPROPERTY(VisibleAnywhere, Category = "Spell")
		bool IsSpellState;
	UPROPERTY(VisibleAnywhere, Category = "Hit")
		bool IsNonHitState;


};
