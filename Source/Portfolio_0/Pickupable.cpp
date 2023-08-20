// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickupable.h"
#include "CharacterHero.h"

// Sets default values
APickupable::APickupable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Component as Root Component.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	// Create Mesh Component and Attach it to the Root Component.
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APickupable::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->SetCollisionProfileName("Pickupable");
}

// Called every frame
void APickupable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Hero)
		return;

	FVector AttractionOrigin = Hero->GetActorLocation();
	float AttractionRadius = 200.f;
	float AttractionStrength = -2000.0f; // Negative strength to attract
	ERadialImpulseFalloff AttractionFalloff = RIF_Constant;
	bool bAffectsVelocity = true;

	MeshComponent->AddRadialForce(
		AttractionOrigin,
		AttractionRadius,
		AttractionStrength,
		AttractionFalloff,
		bAffectsVelocity
	);
}