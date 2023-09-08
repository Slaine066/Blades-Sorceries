// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameModes/GameModeMainMenu.h"
#include "Components/Widgets/MainMenu/MainMenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Actors/CharacterSelector.h"

void AGameModeMainMenu::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

    // Add MainMenuUI to Viewport
    if (UMainMenuUI* MainMenuUI = CreateWidget<UMainMenuUI>(GetWorld(), MainMenuUIClass))
        MainMenuUI->AddToViewport();

    // Spawn CharacterSelector Actors
    FVector Location = FVector(0.f, 0.f, 0.f);
    FRotator Rotation = FRotator::ZeroRotator;

    CharacterSelectorWarrior = Cast<ACharacterSelector>(GetWorld()->SpawnActor(CharacterSelectorWarriorClass, &Location, &Rotation));

    Location.X = 500.f;
    CharacterSelectorMage = Cast<ACharacterSelector>(GetWorld()->SpawnActor(CharacterSelectorMageClass, &Location, &Rotation));

    Location.X = 1000.f;
    CharacterSelectorArcher = Cast<ACharacterSelector>(GetWorld()->SpawnActor(CharacterSelectorArcherClass, &Location, &Rotation));
}

void AGameModeMainMenu::StartPlay()
{
    Super::StartPlay();

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