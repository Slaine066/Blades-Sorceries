// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

/*
 * Character Base Class
 * Character	> CharacterBase		> CharacterHero		> HeroWarrior
 *									> CharacterMob		> MobGoblin
 */

class AWeaponBase;

UCLASS()
class PORTFOLIO_0_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	/*
	* Methods
	*/
	bool Get_IsAttacking() { return IsAttacking; }
	bool Get_IsDead() { return IsDead; }
	
	virtual void Attack();

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*
	* Methods
	*/

	/*
	* Variables
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase> WeaponClassLeft;
	UPROPERTY()
	AWeaponBase* WeaponLeft;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase> WeaponClassRight;
	UPROPERTY()
	AWeaponBase* WeaponRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool IsDead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool IsAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool CanDamage;

private:
	/*
	* Methods
	*/

	/*
	* Variables
	*/
};