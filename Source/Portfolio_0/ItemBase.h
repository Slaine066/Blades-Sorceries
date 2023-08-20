// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItem : uint8
{ 
	/* Attributes Boost */
	HEALTH, 
	HEALTH_REGEN, 
	DAMAGE, 
	ATTACK_SPEED,
	ARMOR, 
	MOVEMENT_SPEED, 
	PICKUP_RANGE, 
	COOLDOWN_REDUCTION, 

	/* Abilities */


	/* Last Element */

};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ATTRIBUTE_BOOST,
	ABILITY
};

UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	COMMON,
	UNCOMMON,
	RARE,
	EPIC,
	LEGENDARY
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItem Item;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType Type;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemGrade Grade;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText Name;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText Description;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	float Amount;
};

UCLASS()
class PORTFOLIO_0_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:
	AItemBase();

	/*
	* Methods Inherited
	*/

	/*
	* Methods
	*/
	FItemData Get_ItemData() { return ItemData; }
	void Set_ItemData(FItemData& _ItemData) { ItemData = _ItemData; }

	void Initialize(class ACharacterHero* Hero);

	UFUNCTION(BlueprintCallable)
	EItem GetItem() { return ItemData.Item; }

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

private:
	FItemData ItemData;
};
