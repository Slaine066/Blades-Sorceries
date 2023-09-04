// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterBase.h"
#include "InputActionValue.h"
#include "CharacterHero.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUpItemEvent, const TArray<class AItemBase*>&, InventoryArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpExpEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIncreaseHealthEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpItemSelectionEvent, const TArray<struct FItemData>&, ChoiceItemArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpItemSelectionEndEvent);

UENUM(BlueprintType)
enum class EJOBCLASS : uint8
{
	WARRIOR,
	MAGE,
	ARCHER
};

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
	// Input Action Functions
	virtual void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void NormalAttack();
	virtual void Fly();
	void Pause();

	const EJOBCLASS GetJobClass() { return JobClass; }

	// Testing Input Action Functions
	void LevelUp();
	void Choice1();
	void Choice2();
	void Choice3();

	UFUNCTION(BlueprintCallable, Category = "Item")
	int GetItemCount() { return Items.Num(); }

	void GainExperience(int Amount);
	void IncreaseHealth(int Amount);
	void GenerateChoices();

	UFUNCTION(BlueprintCallable, Category = "Pickup Items")
	void PickItemSelection(FItemData ItemData);

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

	/*
	* Variables
	*/
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

protected:
	/*
	* Methods Inherited
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/*
	* Methods
	*/
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/*
	* Variables
	*/
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	EJOBCLASS JobClass;

private:
	/*
	* Methods
	*/
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void CheckChoices();
	void AddItem(class AItemBase* Item);
	void Log();

	/*
	* Variables
	*/
	// Spring Arm & Camera
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
	// Sphere Collision
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereCollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UDataTable* ItemsDataTable = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Item")
	TArray<class AItemBase*> Items;
	TArray<struct FItemData> Choices;

	float fDelayEventTime = 0.f;
};