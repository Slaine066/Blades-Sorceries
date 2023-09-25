// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PauseMenu/PauseMenuUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UPauseMenuUI::UPauseMenuUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPauseMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (QuitButton)
	{
		if (!QuitButton->OnClicked.IsBound())
			QuitButton->OnClicked.AddDynamic(this, &UPauseMenuUI::QuitButtonOnClicked);
		if (!QuitButton->OnHovered.IsBound())
			QuitButton->OnHovered.AddDynamic(this, &UPauseMenuUI::QuitButtonOnHovered);
		if (!QuitButton->OnUnhovered.IsBound())
			QuitButton->OnUnhovered.AddDynamic(this, &UPauseMenuUI::QuitButtonOnUnhovered);
	}

	if (ResumeButton)
	{
		if (!ResumeButton->OnClicked.IsBound())
			ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuUI::ResumeButtonOnClicked);
		if (!ResumeButton->OnHovered.IsBound())
			ResumeButton->OnHovered.AddDynamic(this, &UPauseMenuUI::ResumeButtonOnHovered);
		if (!ResumeButton->OnUnhovered.IsBound())
			ResumeButton->OnUnhovered.AddDynamic(this, &UPauseMenuUI::ResumeButtonOnUnhovered);
	}
}

void UPauseMenuUI::QuitButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UPauseMenuUI::QuitButtonOnHovered()
{
	QuitText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UPauseMenuUI::QuitButtonOnUnhovered()
{
	QuitText->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
}

void UPauseMenuUI::ResumeButtonOnClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		RemoveFromViewport();

		PlayerController->SetPause(false);
	}
}

void UPauseMenuUI::ResumeButtonOnHovered()
{
	ResumeText->SetColorAndOpacity(FLinearColor(0.75f, 0.75f, 0.75f, 1.0f));
}

void UPauseMenuUI::ResumeButtonOnUnhovered()
{
	ResumeText->SetColorAndOpacity(FLinearColor(0.55f, 0.55f, 0.55f, 1.0f));
}
