// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/DamageFloating/DamageFloatingActor.h"
#include "Components/Widgets/DamageFloating/DamageFloatingUI.h"
#include "Components/WidgetComponent.h"

ADamageFloatingActor::ADamageFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DamageFloatingSceneComponent"));
	SetRootComponent(RootComponent);

	DamageFloatingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageFloating"));
	DamageFloatingWidgetComponent->SetupAttachment(RootComponent);
	DamageFloatingWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	DamageFloatingWidgetComponent->SetDrawAtDesiredSize(true);

	static ConstructorHelpers::FClassFinder<UDamageFloatingUI>UI_DamageFloating_C(TEXT("'/Game/Portfolio_0/UI/FloatingDamage/WBP_FloatingDamage.WBP_FloatingDamage_C'"));
	if (UI_DamageFloating_C.Succeeded())
		DamageFloatingWidgetComponent->SetWidgetClass(UI_DamageFloating_C.Class);

	// Actor Life
	SetLifeSpan(3.f);
}

void ADamageFloatingActor::SetInfo(float fDamage)
{
	UDamageFloatingUI* DamageFloatingWidget = Cast<UDamageFloatingUI>(DamageFloatingWidgetComponent->GetUserWidgetObject());
	if (DamageFloatingWidget)
		DamageFloatingWidget->SetInfo(fDamage);
}

void ADamageFloatingActor::BeginPlay()
{
	Super::BeginPlay();	
}

void ADamageFloatingActor::BeginDestroy()
{
	Super::BeginDestroy();
}

void ADamageFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move
	AddActorWorldOffset(FVector(0.f, 0.f, Speed) * DeltaTime);
}