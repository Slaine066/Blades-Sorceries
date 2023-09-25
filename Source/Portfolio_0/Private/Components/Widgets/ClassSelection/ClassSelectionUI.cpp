// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/ClassSelection/ClassSelectionUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "SkillBase.h"
#include "Kismet/GameplayStatics.h"

UClassSelectionUI::UClassSelectionUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ClassesDataAsset(TEXT("/Game/Portfolio_0/Data/DT_Classes"));
	if (ClassesDataAsset.Succeeded())
		ClassesDataTable = ClassesDataAsset.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillsDataAsset(TEXT("/Game/Portfolio_0/Data/DT_Skills"));
	if (SkillsDataAsset.Succeeded())
		SkillsDataTable = SkillsDataAsset.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> HoverButtonAsset(TEXT("/Game/Portfolio_0/UI/Class_Selection/Resource/Line_Select_Hover"));
	if (HoverButtonAsset.Succeeded())
		HoverButtonImage = HoverButtonAsset.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> ClickButtonAsset(TEXT("/Game/Portfolio_0/UI/Class_Selection/Resource/Line_Select_Current"));
	if (ClickButtonAsset.Succeeded())
		ClickButtonImage = ClickButtonAsset.Object;

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Character)
		CharacterHero = Cast<ACharacterHero>(Character);
}

void UClassSelectionUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (SelectButton)
	{
		if (!SelectButton->OnClicked.IsBound())
			SelectButton->OnClicked.AddDynamic(this, &UClassSelectionUI::SelectButtonOnClicked);
		if (!SelectButton->OnHovered.IsBound())
			SelectButton->OnHovered.AddDynamic(this, &UClassSelectionUI::SelectButtonOnHovered);
		if (!SelectButton->OnUnhovered.IsBound())
			SelectButton->OnUnhovered.AddDynamic(this, &UClassSelectionUI::SelectButtonOnUnhovered);
	}

	if (ClassButton_1)
	{
		if (!ClassButton_1->OnClicked.IsBound())
			ClassButton_1->OnClicked.AddDynamic(this, &UClassSelectionUI::ClassButton_1OnClicked);
		if (!ClassButton_1->OnHovered.IsBound())
			ClassButton_1->OnHovered.AddDynamic(this, &UClassSelectionUI::ClassButton_1OnHovered);
		if (!ClassButton_1->OnUnhovered.IsBound())
			ClassButton_1->OnUnhovered.AddDynamic(this, &UClassSelectionUI::ClassButton_1OnUnhovered);
	}

	if (ClassButton_2)
	{
		if (!ClassButton_2->OnClicked.IsBound())
			ClassButton_2->OnClicked.AddDynamic(this, &UClassSelectionUI::ClassButton_2OnClicked);
		if (!ClassButton_2->OnHovered.IsBound())
			ClassButton_2->OnHovered.AddDynamic(this, &UClassSelectionUI::ClassButton_2OnHovered);
		if (!ClassButton_2->OnUnhovered.IsBound())
			ClassButton_2->OnUnhovered.AddDynamic(this, &UClassSelectionUI::ClassButton_2OnUnhovered);
	}

	if (ClassButton_3)
	{
		if (!ClassButton_3->OnClicked.IsBound())
			ClassButton_3->OnClicked.AddDynamic(this, &UClassSelectionUI::ClassButton_3OnClicked);
		if (!ClassButton_3->OnHovered.IsBound())
			ClassButton_3->OnHovered.AddDynamic(this, &UClassSelectionUI::ClassButton_3OnHovered);
		if (!ClassButton_3->OnUnhovered.IsBound())
			ClassButton_3->OnUnhovered.AddDynamic(this, &UClassSelectionUI::ClassButton_3OnUnhovered);
	}

	ReadClassData();
	InitClass();
	ChangeClass();
}

void UClassSelectionUI::SelectButtonOnClicked()
{
	if (CharacterHero)
		CharacterHero->ChooseClass(Classes[SelectedClassIndex]->Class);
}

void UClassSelectionUI::SelectButtonOnHovered()
{
	SelectButtonText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UClassSelectionUI::SelectButtonOnUnhovered()
{
	SelectButtonText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UClassSelectionUI::ClassButton_1OnClicked()
{
	SelectedClassIndex = 0;
	ChangeClass();
}

void UClassSelectionUI::ClassButton_1OnHovered()
{
	if (SelectedClassIndex != 0)
		ClassButtonText_1->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UClassSelectionUI::ClassButton_1OnUnhovered()
{
	if (SelectedClassIndex != 0)
		ClassButtonText_1->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
}

void UClassSelectionUI::ClassButton_2OnClicked()
{
	SelectedClassIndex = 1;
	ChangeClass();
}

void UClassSelectionUI::ClassButton_2OnHovered()
{
	if (SelectedClassIndex != 1)
		ClassButtonText_2->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UClassSelectionUI::ClassButton_2OnUnhovered()
{
	if (SelectedClassIndex != 1)
		ClassButtonText_2->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
}

void UClassSelectionUI::ClassButton_3OnClicked()
{
	SelectedClassIndex = 2;
	ChangeClass();
}

void UClassSelectionUI::ClassButton_3OnHovered()
{
	if (SelectedClassIndex != 2)
		ClassButtonText_3->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UClassSelectionUI::ClassButton_3OnUnhovered()
{
	if (SelectedClassIndex != 2)
		ClassButtonText_3->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
}

void UClassSelectionUI::ReadClassData()
{
	ECHARACTER CharacterType = CharacterHero->GetCharacterType();

	TArray<FClassData*> AllClasses;
	ClassesDataTable->GetAllRows("", AllClasses);

	/* Get Classes for current Character */
	for (auto Class : AllClasses)
	{
		if (Class->Character == CharacterType)
			Classes.Add(Class);
	}
}

void UClassSelectionUI::ReadSkillData()
{
	TArray<FSkillData*> AllSkills;
	SkillsDataTable->GetAllRows("", AllSkills);

	Skills.Empty();

	/* Get Skills for current Class */
	for (auto Skill : AllSkills)
	{
		if (Skill->Class == Classes[SelectedClassIndex]->Class)
			Skills.Add(Skill);
	}
}

void UClassSelectionUI::InitClass()
{
	ClassButtonText_1->SetText(Classes[0]->Name);
	ClassButtonText_2->SetText(Classes[1]->Name);
	ClassButtonText_3->SetText(Classes[2]->Name);

	SelectedClassIndex = 0;
}

void UClassSelectionUI::ChangeClass()
{
	ReadSkillData();

	switch (SelectedClassIndex)
	{
	case 0:
		ClassButton_1->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
		ClassButton_2->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		ClassButton_3->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		ClassButton_1->WidgetStyle.Hovered.SetResourceObject(ClickButtonImage);
		ClassButton_2->WidgetStyle.Hovered.SetResourceObject(HoverButtonImage);
		ClassButton_3->WidgetStyle.Hovered.SetResourceObject(HoverButtonImage);
		ClassButtonText_1->SetColorAndOpacity(FLinearColor(0.58f, 0.19f, 0.19f, 1.0f));
		ClassButtonText_2->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		ClassButtonText_3->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case 1:
		ClassButton_1->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		ClassButton_2->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
		ClassButton_3->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		ClassButton_1->WidgetStyle.Hovered.SetResourceObject(HoverButtonImage);
		ClassButton_2->WidgetStyle.Hovered.SetResourceObject(ClickButtonImage);
		ClassButton_3->WidgetStyle.Hovered.SetResourceObject(HoverButtonImage);
		ClassButtonText_1->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		ClassButtonText_2->SetColorAndOpacity(FLinearColor(0.58f, 0.19f, 0.19f, 1.0f));
		ClassButtonText_3->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	case 2:
		ClassButton_1->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		ClassButton_2->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		ClassButton_3->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
		ClassButton_1->WidgetStyle.Hovered.SetResourceObject(HoverButtonImage);
		ClassButton_2->WidgetStyle.Hovered.SetResourceObject(HoverButtonImage);
		ClassButton_3->WidgetStyle.Hovered.SetResourceObject(ClickButtonImage);
		ClassButtonText_1->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		ClassButtonText_2->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		ClassButtonText_3->SetColorAndOpacity(FLinearColor(0.58f, 0.19f, 0.19f, 1.0f));
		break;
	}

	ClassImage->SetBrushFromTexture(Classes[SelectedClassIndex]->ClassImage);

	ClassDescription->SetText(Classes[SelectedClassIndex]->Description);

	SlotImage_1->SetBrushFromTexture(Skills[0]->SlotImage);
	SlotImage_2->SetBrushFromTexture(Skills[1]->SlotImage);
	SlotImage_3->SetBrushFromTexture(Skills[2]->SlotImage);

	SkillImage_1->SetBrushFromTexture(Skills[0]->SkillImage);
	SkillImage_2->SetBrushFromTexture(Skills[1]->SkillImage);
	SkillImage_3->SetBrushFromTexture(Skills[2]->SkillImage);

	SkillImage_1->SetToolTipText(Skills[0]->Name);
	SkillImage_2->SetToolTipText(Skills[1]->Name);
	SkillImage_3->SetToolTipText(Skills[2]->Name);
}
