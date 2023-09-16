// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameModes/GameModeMainMenu.h"
#include "Components/Widgets/MainMenu/MainMenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Actors/CharacterSelector.h"

AGameModeMainMenu::AGameModeMainMenu()
{
    static ConstructorHelpers::FClassFinder<UMainMenuUI>WBP_MainMenu_C(TEXT("'/Game/Portfolio_0/UI/WBP_MainMenu.WBP_MainMenu_C'"));
    if (WBP_MainMenu_C.Succeeded())
        MainMenuUIClass = WBP_MainMenu_C.Class;

    static ConstructorHelpers::FClassFinder<ACharacterSelector>WBP_CharacterSelectorWarrior_C(TEXT("'/Game/Portfolio_0/Blueprint/BP_CharacterSelectorWarrior.BP_CharacterSelectorWarrior_C'"));
    if (WBP_CharacterSelectorWarrior_C.Succeeded())
        CharacterSelectorWarriorClass = WBP_CharacterSelectorWarrior_C.Class;

    static ConstructorHelpers::FClassFinder<ACharacterSelector>WBP_CharacterSelectorMage_C(TEXT("'/Game/Portfolio_0/Blueprint/BP_CharacterSelectorMage.BP_CharacterSelectorMage_C'"));
    if (WBP_CharacterSelectorMage_C.Succeeded())
        CharacterSelectorMageClass = WBP_CharacterSelectorMage_C.Class;

    static ConstructorHelpers::FClassFinder<ACharacterSelector>WBP_CharacterSelectorArcher_C(TEXT("'/Game/Portfolio_0/Blueprint/BP_CharacterSelectorArcher.BP_CharacterSelectorArcher_C'"));
    if (WBP_CharacterSelectorArcher_C.Succeeded())
        CharacterSelectorArcherClass = WBP_CharacterSelectorArcher_C.Class;
}

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
        PlayerController->SetInputMode(FInputModeUIOnly());
        PlayerController->bShowMouseCursor = true;
    }
}

void AGameModeMainMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}