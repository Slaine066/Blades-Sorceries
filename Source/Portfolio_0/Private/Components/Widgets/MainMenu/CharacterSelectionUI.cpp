// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/MainMenu/CharacterSelectionUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Portfolio_0LoadingScreen.h"
#include "Components/Widgets/MainMenu/MainMenuUI.h"
#include "Actors/CharacterSelector.h"
#include "Actors/GameModes/GameModeMainMenu.h"
#include "GameInstanceCustom.h"

UCharacterSelectionUI::UCharacterSelectionUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> LeftArrowUnhoverAsset(TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/Arrow_Left_Normal"));
	if (LeftArrowUnhoverAsset.Succeeded())
		LeftArrowUnhoverImage = LeftArrowUnhoverAsset.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> RightArrowUnhoverAsset(TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/Arrow_Right_Normal"));
	if (RightArrowUnhoverAsset.Succeeded())
		RightArrowUnhoverImage = RightArrowUnhoverAsset.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> LeftArrowHoverAsset(TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/Arrow_Left_Hover"));
	if (LeftArrowHoverAsset.Succeeded())
		LeftArrowHoverImage = LeftArrowHoverAsset.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> RightArrowHoverAsset(TEXT("/Game/Portfolio_0/UI/Main_Menu/Resource/Arrow_Right_Hover"));
	if (RightArrowHoverAsset.Succeeded())
		RightArrowHoverImage = RightArrowHoverAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterDataAsset(TEXT("/Game/Portfolio_0/Data/DT_Characters"));
	if (CharacterDataAsset.Succeeded())
		CharactersDataTable = CharacterDataAsset.Object;
}

void UCharacterSelectionUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		if(!BackButton->OnClicked.IsBound()) 
			BackButton->OnClicked.AddDynamic(this, &UCharacterSelectionUI::BackButtonOnClicked);
		if (!BackButton->OnHovered.IsBound())
			BackButton->OnHovered.AddDynamic(this, &UCharacterSelectionUI::BackButtonOnHovered);
		if (!BackButton->OnUnhovered.IsBound())
			BackButton->OnUnhovered.AddDynamic(this, &UCharacterSelectionUI::BackButtonOnUnhovered);
	}

	if (PlayButton)
	{
		if (!PlayButton->OnClicked.IsBound())
			PlayButton->OnClicked.AddDynamic(this, &UCharacterSelectionUI::PlayButtonOnClicked);
		if (!PlayButton->OnHovered.IsBound())
			PlayButton->OnHovered.AddDynamic(this, &UCharacterSelectionUI::PlayButtonOnHovered);
		if (!PlayButton->OnUnhovered.IsBound())
			PlayButton->OnUnhovered.AddDynamic(this, &UCharacterSelectionUI::PlayButtonOnUnhovered);
	}

	if (LeftArrowButton)
	{
		if (!LeftArrowButton->OnClicked.IsBound())
			LeftArrowButton->OnClicked.AddDynamic(this, &UCharacterSelectionUI::LeftArrowButtonOnClicked);
		if (!LeftArrowButton->OnHovered.IsBound())
			LeftArrowButton->OnHovered.AddDynamic(this, &UCharacterSelectionUI::LeftArrowButtonOnHovered);
		if (!LeftArrowButton->OnUnhovered.IsBound())
			LeftArrowButton->OnUnhovered.AddDynamic(this, &UCharacterSelectionUI::LeftArrowButtonOnUnhovered);
	}

	if (RightArrowButton)
	{
		if (!RightArrowButton->OnClicked.IsBound())
			RightArrowButton->OnClicked.AddDynamic(this, &UCharacterSelectionUI::RightArrowButtonOnClicked);
		if (!RightArrowButton->OnHovered.IsBound())
			RightArrowButton->OnHovered.AddDynamic(this, &UCharacterSelectionUI::RightArrowButtonOnHovered);
		if (!RightArrowButton->OnUnhovered.IsBound())
			RightArrowButton->OnUnhovered.AddDynamic(this, &UCharacterSelectionUI::RightArrowButtonOnUnhovered);
	}
	
	ReadCharacterData();
	ChangeCharacter();
}

void UCharacterSelectionUI::BackButtonOnClicked()
{
	RemoveFromViewport();
	
	UMainMenuUI* MainMenuUI = Cast<UMainMenuUI>(WidgetOwner);
	if (MainMenuUI)
		MainMenuUI->StartFadeIn();
}

void UCharacterSelectionUI::BackButtonOnHovered()
{
	BackText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UCharacterSelectionUI::BackButtonOnUnhovered()
{
	BackText->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
}

void UCharacterSelectionUI::PlayButtonOnClicked()
{
	// Set Selected Character
	UGameInstanceCustom* GameInstanceCustom = Cast<UGameInstanceCustom>(GetGameInstance());
	if (GameInstanceCustom)
		GameInstanceCustom->Set_SelectedCharacter(SelectedCharacterIndex);

	// Start Loading Screen
	IPortfolio_0LoadingScreenModule& LoadingScreenModule = IPortfolio_0LoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(false, 0.f);

	// Open Gameplay Level
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Portfolio_0/Maps/Map_1"));
}

void UCharacterSelectionUI::PlayButtonOnHovered()
{
	PlayText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UCharacterSelectionUI::PlayButtonOnUnhovered()
{
	PlayText->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
}

void UCharacterSelectionUI::LeftArrowButtonOnClicked()
{
	if (Characters.IsEmpty())
		return;

	SelectedCharacterIndex -= 1;

	if (SelectedCharacterIndex < 0)
		SelectedCharacterIndex = Characters.Num() - 1;

	ChangeCharacter();
}

void UCharacterSelectionUI::LeftArrowButtonOnHovered()
{
	LeftArrowImage->SetBrushFromTexture(LeftArrowHoverImage);
}

void UCharacterSelectionUI::LeftArrowButtonOnUnhovered()
{
	LeftArrowImage->SetBrushFromTexture(LeftArrowUnhoverImage);
}

void UCharacterSelectionUI::RightArrowButtonOnClicked()
{
	if (Characters.IsEmpty())
		return;

	SelectedCharacterIndex += 1;

	if (SelectedCharacterIndex > Characters.Num() - 1)
		SelectedCharacterIndex = 0;

	ChangeCharacter();
}

void UCharacterSelectionUI::RightArrowButtonOnHovered()
{
	RightArrowImage->SetBrushFromTexture(RightArrowHoverImage);
}

void UCharacterSelectionUI::RightArrowButtonOnUnhovered()
{
	RightArrowImage->SetBrushFromTexture(RightArrowUnhoverImage);
}

void UCharacterSelectionUI::ReadCharacterData()
{
	CharactersDataTable->GetAllRows("", Characters);

	RightArrowImage->SetBrushFromTexture(RightArrowUnhoverImage);
}

void UCharacterSelectionUI::ChangeCharacter()
{
	CharacterText->SetText(Characters[SelectedCharacterIndex]->Name);
	
	CharacterDescriptionText->SetText(Characters[SelectedCharacterIndex]->Description);
	
	ClassImage1->SetBrushFromTexture(Characters[SelectedCharacterIndex]->ClassImages[0]);
	ClassImage2->SetBrushFromTexture(Characters[SelectedCharacterIndex]->ClassImages[1]);
	ClassImage3->SetBrushFromTexture(Characters[SelectedCharacterIndex]->ClassImages[2]);

	ClassImage1->SetToolTipText(Characters[SelectedCharacterIndex]->Classes[0]);
	ClassImage2->SetToolTipText(Characters[SelectedCharacterIndex]->Classes[1]);
	ClassImage3->SetToolTipText(Characters[SelectedCharacterIndex]->Classes[2]);

	CharacterSelectorImage->SetBrushFromMaterial(Characters[SelectedCharacterIndex]->CharacterMaterial);
}
