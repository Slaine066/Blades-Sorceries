// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterBase.h"
#include "InputActionValue.h"
#include "../../../Util/Utility.h"
#include "CharacterHero.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUpItemEvent, const TArray<class AItemBase*>&, InventoryArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpExpEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIncreaseHealthEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpItemSelectionEvent, const TArray<struct FItemData>&, ChoiceItemArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpItemSelectionEndEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpClassSelectionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpClassSelectionEndEvent);

UCLASS()
class PORTFOLIO_0_API ACharacterHero : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	ACharacterHero();

	/* Methods Inherited */
	virtual void Die() override;

	/* Methods */
	const ECHARACTER GetCharacterType() { return CharacterType; }
	TArray<class ASkillBase*> Get_Skills() { return Skills; }
	int GetItemCount() { return Items.Num(); }
	void GainExperience(int Amount);
	void IncreaseHealth(int Amount);
	void GenerateChoices();

	// Input Action Functions
	virtual void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void NormalAttack();
	virtual void Fly();

	// Testing Input Action Functions
	void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "Pickup Items")
	void PickItemSelection(FItemData ItemData);
	UFUNCTION(BlueprintCallable, Category = "Level Up")
	void ChooseClass(ECLASS Class);

	UFUNCTION(BlueprintCallable, Category = "Pickup Items")
	void TriggerPickupItemEvent(const TArray<class AItemBase*>& InventoryArray);
	UFUNCTION(BlueprintCallable, Category = "Pickup Items")
	void TriggerPickupExpEvent();
	UFUNCTION(BlueprintCallable, Category = "Pickup Items")
	void TriggerIncreaseHealth();
	UFUNCTION(BlueprintCallable, Category = "Level Up")
	void TriggerLevelUpItemSelection(const TArray<struct FItemData>& ChoiceItemArray);
	UFUNCTION(BlueprintCallable, Category = "Level Up")
	void TriggerLevelUpItemSelectionEnd();
	UFUNCTION(BlueprintCallable, Category = "Level Up")
	void TriggerLevelUpClassSelection();
	UFUNCTION(BlueprintCallable, Category = "Level Up")
	void TriggerLevelUpClassSelectionEnd();



	/* Variables */
	UPROPERTY(BlueprintAssignable, Category = "Pickup Items")
	FOnPickUpItemEvent OnPickUpItem;
	UPROPERTY(BlueprintAssignable, Category = "Pickup Items")
	FOnPickUpExpEvent OnPickUpExp;
	UPROPERTY(BlueprintAssignable, Category = "Pickup Items")
	FOnIncreaseHealthEvent OnIncreaseHealth;
	UPROPERTY(BlueprintAssignable, Category = "Level Up")
	FOnLevelUpItemSelectionEvent OnLevelUpItemSelection;
	UPROPERTY(BlueprintAssignable, Category = "Level Up")
	FOnLevelUpItemSelectionEndEvent OnLevelUpItemSelectionEnd;
	UPROPERTY(BlueprintAssignable, Category = "Level Up")
	FOnLevelUpClassSelectionEvent OnLevelUpClassSelection;
	UPROPERTY(BlueprintAssignable, Category = "Level Up")
	FOnLevelUpClassSelectionEndEvent OnLevelUpClassSelectionEnd;

protected:
	/* Methods Inherited */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/* Methods */
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/* Variables */
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	ECHARACTER CharacterType;
	ECLASS CharacterClass;

private:
	/* Methods */
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void InitSkills();
	void CheckChoices();
	void AddItem(class AItemBase* Item);
	void Log();

	/* Variables */
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereCollisionComponent;

	// Items
	UPROPERTY(EditAnywhere, Category = "Item")
	class UDataTable* ItemsDataTable = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Item")
	TArray<class AItemBase*> Items;
	TArray<struct FItemData> Choices;

	// Skill
	UPROPERTY(EditAnywhere, Category = "Skill")
	class UDataTable* SkillsDataTable = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	TArray<class ASkillBase*> Skills;

	float fDelayEventTime = 0.f;
};