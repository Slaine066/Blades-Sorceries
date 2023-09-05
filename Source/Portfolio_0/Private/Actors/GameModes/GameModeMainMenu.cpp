// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameModes/GameModeMainMenu.h"
#include "Components/Widgets/MainMenu/MainMenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AGameModeMainMenu::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

    // Add Main Menu UI to Viewport
    if (UMainMenuUI* MainMenuUI = CreateWidget<UMainMenuUI>(GetWorld(), MainMenuUIClass))
        MainMenuUI->AddToViewport();
}

void AGameModeMainMenu::StartPlay()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        // Show Mouse Cursor
        PlayerController->bShowMouseCursor = true;
        PlayerController->bEnableClickEvents = true;
        PlayerController->bEnableMouseOverEvents = true;
    }
}

void AGameModeMainMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}