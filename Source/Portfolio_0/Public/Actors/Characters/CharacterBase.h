// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/TimelineComponent.h>
#include "CharacterBase.generated.h"

/*
 * Character Base Class
 * Character	> CharacterBase		> CharacterHero		> HeroWarrior
 *									> CharacterMob		> MobGoblin
 */

class AWeaponBase;
class AClothPartsBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitDamageEvent, int, iDamage);

USTRUCT(BlueprintType)
struct FAttributes
{
	GENERATED_USTRUCT_BODY()

	FAttributes() {}

	// Level & Experience
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExperienceMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Experience;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthRegen;

	// Damage & Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor;

	// Utility
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PickupRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownReduction;
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
	FAttributes& Get_Attributes_Ref() { return Attributes; }
	bool Get_IsDead() { return IsDead; }
	bool Get_IsHit() { return IsHit; }
	bool Get_IsAttacking() { return IsAttacking; }
	bool Get_CanDamage() { return CanDamage; }
	void Set_HealthMax(int HealthMax) { Attributes.HealthMax = HealthMax; }
	void Set_HealthRegen(float HealthRegen) { Attributes.HealthRegen = HealthRegen; }
	void Set_Damage(int Damage) { Attributes.Damage = Damage; }
	void Set_AttackSpeed(float AttackSpeed) { Attributes.AttackSpeed = AttackSpeed; }
	void Set_Armor(float Armor) { Attributes.Armor = Armor; }
	void Set_MovementSpeed(float MovementSpeed) { Attributes.MovementSpeed = MovementSpeed; }
	void Set_PickupRange(float PickupRange) { Attributes.PickupRange = PickupRange; }
	void Set_CooldownReduction(float CooldownReduction) { Attributes.CooldownReduction = CooldownReduction; }
	
	virtual void Attack();
	virtual void Hit();
	virtual void Die();

	UPROPERTY(BlueprintAssignable, Category = "HitDamage")
	FOnHitDamageEvent OnHitDamage;

	UFUNCTION(BlueprintCallable, Category = "HitDamage")
	void TriggerHitDamageEvent(int iDamage);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void FloatingDamageFont(float Damage);

	/*
	* Variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitDamage")
	FLinearColor HitDamageColorRGBA{1.f, 1.f, 1.f, 1.f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitDamage")
	FVector LocationOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitDamage")
	int FontSize = 24;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitDamage")
	int OutlineSize = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitDamage")
	FLinearColor HitDamageOutlineColorRGBA {0.f, 0.f, 0.f, 1.f	};

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

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<class ADamageFloatingActor> DamageFloatingClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float SpawnFloatingSpeed;

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

	UFUNCTION()
	void StartDissolveTimeline();
	UFUNCTION()
	void Dissolve(float Value);

	/*
	* Variables
	*/
	FTimeline DissolveTimeline;

	UPROPERTY(EditAnywhere, Category = "Effects")
	float DissolveAfter;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UCurveFloat* DissolveFloatCurve;
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* DissolveSystem;
};