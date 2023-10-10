// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerHpWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Actors/Characters/Hero/CharacterHero.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"

UPlayerHpWidget::UPlayerHpWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ACharacterHero* Hero = Cast<ACharacterHero>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Hero)
		return;

	ECHARACTER Character = Hero->GetCharacterType();
	switch (Character)
	{
	case ECHARACTER::WARRIOR:
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> CharacterProfileMaterialWarriorAsset(TEXT("/Game/Portfolio_0/UI/HealthBar/M_CharacterSelectorProfileWarrior"));
		if (CharacterProfileMaterialWarriorAsset.Succeeded())
			CharacterProfileMaterial = CharacterProfileMaterialWarriorAsset.Object;
		break;
	}
	case ECHARACTER::MAGE:
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> CharacterProfileMaterialMageAsset(TEXT("/Game/Portfolio_0/UI/HealthBar/M_CharacterSelectorProfileMage"));
		if (CharacterProfileMaterialMageAsset.Succeeded())
			CharacterProfileMaterial = CharacterProfileMaterialMageAsset.Object;
		break;
	}
	case ECHARACTER::ARCHER:
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> CharacterProfileMaterialArcherAsset(TEXT("/Game/Portfolio_0/UI/HealthBar/M_CharacterSelectorProfileArcher"));
		if (CharacterProfileMaterialArcherAsset.Succeeded())
			CharacterProfileMaterial = CharacterProfileMaterialArcherAsset.Object;
		break;
	}	
	}
}

void UPlayerHpWidget::UpdateLevel(FAttributes PlayerAttribute)
{
	TextLevel->SetText(FText::FromString(FString::FromInt(PlayerAttribute.Level)));
}

void UPlayerHpWidget::UpdateHp(FAttributes PlayerAttribute)
{
	TextMaxHp->SetText(FText::FromString(FString::FromInt(PlayerAttribute.HealthMax)));
	TextCurrentHp->SetText(FText::FromString(FString::FromInt(PlayerAttribute.Health)));

	HpRatio = (float)PlayerAttribute.Health / PlayerAttribute.HealthMax;

	ProgressHpBar->SetPercent(HpRatio);
}

void UPlayerHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ImageCharacter->SetBrushFromMaterial(CharacterProfileMaterial);
}
