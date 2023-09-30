// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/ClothPartsBase.h"
#include "Actors/Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"

AClothPartsBase::AClothPartsBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Component as Root Component.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	// Create Mesh Component and Attach it to the Root Component.
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AClothPartsBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AClothPartsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}