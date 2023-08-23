// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemBase.h"
#include "Actors/Characters/Hero/CharacterHero.h"

AItemBase::AItemBase()
{
}

void AItemBase::Initialize(ACharacterHero* Hero)
{
	if (!Hero)
		return;

	switch (ItemData.Item)
	{
		case EItem::HEALTH:
		{		
			int HealthMax = Hero->Get_Attributes().HealthMax;
			int HealthBonus = HealthMax / ItemData.Amount;
			HealthMax += HealthBonus;
			Hero->Set_HealthMax(HealthMax);
			Hero->TriggerIncreaseHealth();
			break;
		}
		case EItem::HEALTH_REGEN:
		{
			Hero->Set_HealthRegen(ItemData.Amount);
			break;
		}
		case EItem::DAMAGE:
		{
			int Damage = Hero->Get_Attributes().Damage;
			Damage += ItemData.Amount;
			Hero->Set_Damage(Damage);
			break;
		}
		case EItem::ATTACK_SPEED:
		{
			float AttackSpeed = Hero->Get_Attributes().AttackSpeed;
			AttackSpeed += ItemData.Amount;
			Hero->Set_AttackSpeed(AttackSpeed);
			break;
		}
		case EItem::ARMOR:
		{
			float Armor = Hero->Get_Attributes().Armor;
			Armor += ItemData.Amount;
			Hero->Set_Armor(Armor);
			break;
		}
		case EItem::MOVEMENT_SPEED:
		{
			float MovementSpeed = Hero->Get_Attributes().MovementSpeed;
			MovementSpeed += ItemData.Amount;
			Hero->Set_MovementSpeed(MovementSpeed);
			break;
		}
		case EItem::PICKUP_RANGE:
		{
			float PickupRange = Hero->Get_Attributes().PickupRange;
			PickupRange += ItemData.Amount;
			Hero->Set_PickupRange(PickupRange);
			break;
		}
		case EItem::COOLDOWN_REDUCTION:
		{
			float CooldownReduction = Hero->Get_Attributes().CooldownReduction;
			CooldownReduction += ItemData.Amount;
			Hero->Set_CooldownReduction(CooldownReduction);
			break;
		}
	}
}

void AItemBase::BeginPlay()
{
}

void AItemBase::Tick(float DeltaTime)
{
	if (ItemData.Type == EItemType::ATTRIBUTE_BOOST)
		return;
}
