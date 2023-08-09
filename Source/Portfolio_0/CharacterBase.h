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
class AClothPartsBase;

USTRUCT(BlueprintType)
struct FAttributes
{
	GENERATED_USTRUCT_BODY()

	FAttributes() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;
};

UCLASS()
class PORTFOLIO_0_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	/*
	* Methods
	*/
	FAttributes Get_Attributes() { return Attributes; }
	bool Get_IsDead() { return IsDead; }
	bool Get_IsHit() { return IsHit; }
	bool Get_IsAttacking() { return IsAttacking; }
	bool Get_CanDamage() { return CanDamage; }
	
	virtual void Attack();
	virtual void Hit();
	virtual void Die();

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
	UFUNCTION()
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	/*
	* Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributes Attributes;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase> WeaponClassLeft;
	UPROPERTY()
	AWeaponBase* WeaponLeft;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase> WeaponClassRight;
	UPROPERTY()
	AWeaponBase* WeaponRight;

	UPROPERTY(EditDefaultsOnly, Category = "Cloth")
	TSubclassOf<AClothPartsBase> ClothHairClass;
	UPROPERTY()
	AClothPartsBase* ClothHair;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool IsDead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool IsHit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool IsAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool CanDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* HitMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* DeathMontage;

private:
	/*
	* Methods
	*/
	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
	void OnMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	/*
	* Variables
	*/
	
};