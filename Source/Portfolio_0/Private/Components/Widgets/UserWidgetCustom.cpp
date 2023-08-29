// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/UserWidgetCustom.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Blueprint/WidgetTree.h"


UUserWidgetCustom::UUserWidgetCustom(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UUserWidgetCustom::NativeOnInitialized()
{
	//Only one called at create
	Super::NativeOnInitialized();
}

void UUserWidgetCustom::NativePreConstruct()
{
	//Called every add viewport time
	Super::NativePreConstruct();

}

void UUserWidgetCustom::NativeDestruct()
{
	//Called every remove viewport time
	Super::NativeDestruct();

}

void UUserWidgetCustom::NativeConstruct()
{
	Super::NativeConstruct();


}

FReply UUserWidgetCustom::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return Reply;
}
