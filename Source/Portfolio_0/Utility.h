// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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
