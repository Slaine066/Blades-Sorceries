// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerSkillBarUI.h"
#include "Components/Image.h"
#include "SkillBase.h"

UPlayerSkillBarUI::UPlayerSkillBarUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Visibility = ESlateVisibility::Hidden;
}

void UPlayerSkillBarUI::UpdateSkills(TArray<class ASkillBase*> Skills)
{
	SlotImage_1->SetBrushFromTexture(Skills[0]->Get_SkillData().SlotImage);
	SlotImage_2->SetBrushFromTexture(Skills[1]->Get_SkillData().SlotImage);
	SlotImage_3->SetBrushFromTexture(Skills[2]->Get_SkillData().SlotImage);

	SkillImage_1->SetBrushFromTexture(Skills[0]->Get_SkillData().SkillImage);
	SkillImage_2->SetBrushFromTexture(Skills[1]->Get_SkillData().SkillImage);
	SkillImage_3->SetBrushFromTexture(Skills[2]->Get_SkillData().SkillImage);

	SkillImage_1->SetToolTipText(Skills[0]->Get_SkillData().Description);
	SkillImage_2->SetToolTipText(Skills[1]->Get_SkillData().Description);
	SkillImage_3->SetToolTipText(Skills[2]->Get_SkillData().Description);
}

void UPlayerSkillBarUI::NativeConstruct()
{
	Super::NativeConstruct();
}
