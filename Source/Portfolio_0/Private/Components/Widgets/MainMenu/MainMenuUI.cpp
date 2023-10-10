// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/MainMenu/MainMenuUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Widgets/MainMenu/CharacterSelectionUI.h"
#include "Kismet/KismetSystemLibrary.h"

UMainMenuUI::UMainMenuUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMainMenuUI::StartFadeIn()
{
	PlayAnimation(FadeIn);
}

void UMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenuUI::StartGameButtonOnClicked);
		StartGameButton->OnHovered.AddDynamic(this, &UMainMenuUI::StartGameButtonOnHovered);
		StartGameButton->OnUnhovered.AddDynamic(this, &UMainMenuUI::StartGameButtonOnUnhovered);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenuUI::SettingsButtonOnClicked);
		SettingsButton->OnHovered.AddDynamic(this, &UMainMenuUI::SettingsButtonOnHovered);
		SettingsButton->OnUnhovered.AddDynamic(this, &UMainMenuUI::SettingsButtonOnUnhovered);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuUI::ExitButtonOnClicked);
		ExitButton->OnHovered.AddDynamic(this, &UMainMenuUI::ExitButtonOnHovered);
		ExitButton->OnUnhovered.AddDynamic(this, &UMainMenuUI::ExitButtonOnUnhovered);
	}

	FadeOutFinishedDelegate.BindDynamic(this, &UMainMenuUI::FadeOutFinished);
	BindToAnimationFinished(FadeOut, FadeOutFinishedDelegate);
}

void UMainMenuUI::FadeOutFinished()
{
	// Add Character Selection UI to Viewport
	if (!CharacterSelectionUI)
	{
		CharacterSelectionUI = CreateWidget<UCharacterSelectionUI>(GetWorld(), CharacterSelectionUIClass);
		CharacterSelectionUI->Set_WidgetOwner(this);
	}

	CharacterSelectionUI->AddToViewport();
}

void UMainMenuUI::StartGameButtonOnClicked()
{
	PlayAnimation(FadeOut);
}

void UMainMenuUI::StartGameButtonOnHovered()
{
	StartGameText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UMainMenuUI::StartGameButtonOnUnhovered()
{
	StartGameText->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
}

void UMainMenuUI::SettingsButtonOnClicked()
{
}

void UMainMenuUI::SettingsButtonOnHovered()
{
	SettingsText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UMainMenuUI::SettingsButtonOnUnhovered()
{
	SettingsText->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
}

void UMainMenuUI::ExitButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UMainMenuUI::ExitButtonOnHovered()
{
	ExitText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UMainMenuUI::ExitButtonOnUnhovered()
{
	ExitText->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
}