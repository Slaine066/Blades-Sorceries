// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/UserWidgetCustom.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Blueprint/WidgetTree.h"


UUserWidgetCustom::UUserWidgetCustom(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	ExampleButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("ExampleButtonName"));
}

void UUserWidgetCustom::NativeConstruct()
{
	Super::NativeConstruct();

	//Bind delegates here
}
