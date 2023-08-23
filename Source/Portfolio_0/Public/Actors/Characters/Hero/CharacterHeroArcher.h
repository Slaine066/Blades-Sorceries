// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHero.h"
#include "../../Projectiles/ArrowProjectile.h"
#include "CharacterHeroArcher.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API ACharacterHeroArcher : public ACharacterHero
{
	GENERATED_BODY()

public:
	ACharacterHeroArcher();

	void OnNormalAttack();
	FVector GetMousePos() const { return m_vMousePosition; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AArrowProjectile> ProjectileClass;




protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

private:
	void SetWeapon();
	void NormalAttackFunc(const FInputActionValue& Value);
	void UpdateMousePos();
	void ArrowFire(); // NormalAttack
	void Fire(FVector vDirection);
	void HandlePicking();

private:
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* NormalAttackArcherAction;

	UPROPERTY(EditAnywhere, Category = "NormalAttack")
	UAnimMontage* NormalAttack;

	UPROPERTY(EditAnywhere, Category = "Hit")
	UAnimMontage* Hit;

	UPROPERTY(EditAnywhere, Category = "Death")
	UAnimMontage* Death;

	UPROPERTY(EditAnywhere, Category = "NormalAttack")
	bool bIsAttack;

	FVector m_vMousePosition;

	FVector Temp;
	

	
	float fShootTime = 0.f;
	bool bShoot = false;
};
