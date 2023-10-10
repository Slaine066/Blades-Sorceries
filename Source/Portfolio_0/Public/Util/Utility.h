// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECHARACTER : uint8
{
	WARRIOR,
	MAGE,
	ARCHER
};

UENUM(BlueprintType)
enum class ECLASS : uint8
{
	BERSERKER,
	GUARDIAN,
	DEATH_KNIGHT,
	PYROMANCER,
	ELECTROMANCER,
	ARCANIST,
	RANGER,
	HUNTER,
	DEMON_HUNTER,
	NONE
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ATTRIBUTE_BOOST,
	SKILL_1,
	SKILL_2,
	SKILL_3
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

/* Enum used for AddOnScreenDebugMessage(). */
UENUM()
enum class ELOG
{
	TIMER,
	MOB_COUNT_LIMIT,
	MOB_COUNT,
	ATTRIBUTES,
	LEVEL,
	EXPERIENCE_MAX,
	EXPERIENCE,
	HEALTH_MAX,
	HEALTH,
	HEALTH_REGEN,
	DAMAGE,
	ATTACK_SPEED,
	ARMOR,
	MOVEMENT_SPEED,
	PICKUP_RANGE,
	COOLDOWN_REDUCTION,
	ITEMS,
	ITEM_CHOICE_1,
	ITEM_CHOICE_2,
	ITEM_CHOICE_3,
};

class PORTFOLIO_0_API Utility
{
public:
	Utility();
	~Utility();
};
