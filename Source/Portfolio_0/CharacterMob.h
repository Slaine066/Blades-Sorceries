// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterMob.generated.h"

class UBehaviorTree;

UCLASS()
class PORTFOLIO_0_API ACharacterMob : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterMob();

	/*
	* Methods Inherited
	*/
	virtual void Attack() override;

	/*
	* Methods
	*/
	// AnimNotify
	void OnSpawn();

	bool Get_IsSpawned() { return IsSpawned; }
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool IsSpawned = false;

private:
	/*
	* Methods
	*/
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/*
	* Variables
	*/
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* SpawnMontage = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* NormalAttackMontage = nullptr;
};
