// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "../Util/Utility.h"
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
	ADDITIONAL_PROJECTILE,
	SKILL_DAMAGE,
	SKILL_COOLDOWN_REDUCTION,
	SKILL_DURATION,
	SKILL_SPEED,
	SKILL_SIZE
};

USTRUCT(BlueprintType, meta = (AbleSplitPin))
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EItem Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EItemType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	ECLASS Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EItemGrade Grade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	UTexture2D* Slot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	float Amount;
};

UCLASS(BlueprintType)
class PORTFOLIO_0_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:
	AItemBase();

	/* Methods Inherited */

	/* Methods */
	FItemData Get_ItemData() { return ItemData; }
	void Set_ItemData(FItemData& _ItemData) { ItemData = _ItemData; }

	void Initialize(class ACharacterHero* Hero);

	UFUNCTION(BlueprintCallable)
	EItem GetItem() { return ItemData.Item; }

	/* Variables */

protected:
	/* Methods Inherited */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Methods */

	/* Variables */

private:
	FItemData ItemData;
};
