// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controllers/Player/PlayerControllerCustom.h"
#include "Components/Widgets/UserWidgetCustom.h"

APlayerControllerCustom::APlayerControllerCustom()
{
	UUserWidgetCustom* UserInterface = CreateWidget<UUserWidgetCustom>(this, UUserWidgetCustom::StaticClass());
	FInputModeGameAndUI UIMode;
	UIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	UIMode.SetHideCursorDuringCapture(false);
	SetInputMode(UIMode);
	// Z-order, this just makes it render on the very top
	// you choose render order
	UserInterface->AddToViewport(9999);
	

}

void APlayerControllerCustom::BeginPlay()
{
	Super::BeginPlay();

		
}
