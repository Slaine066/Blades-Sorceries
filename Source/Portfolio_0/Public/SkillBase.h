// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Util/Utility.h"
#include "Engine/DataTable.h"
#include "SkillBase.generated.h"

USTRUCT(BlueprintType, meta = (AbleSplitPin))
struct FSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	ECHARACTER Character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	ECLASS Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	EItemType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	UTexture2D* SlotImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	UTexture2D* SkillImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float Projectiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float CooldownReduction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float Size;
};

UCLASS()
class PORTFOLIO_0_API ASkillBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillBase();

	/* Methods */
	FSkillData Get_SkillData() { return SkillData; }
	void Set_SkillData(FSkillData& _SkillData) { SkillData = _SkillData; }

	/* Variables */

protected:
	/* Methods */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Variables */

private:
	/* Methods */

	/* Variables */
	FSkillData SkillData;
};
