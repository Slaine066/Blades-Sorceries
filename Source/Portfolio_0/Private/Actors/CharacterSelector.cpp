// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CharacterSelector.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Actors/ClothPartsBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
ACharacterSelector::ACharacterSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = MeshComponent;

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(RootComponent);
	SceneCaptureComponent->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

	// Don't show background
	SceneCaptureComponent->ShowOnlyActors = { this };

	SceneCaptureComponentProfile = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponentProfile"));
	SceneCaptureComponentProfile->SetupAttachment(RootComponent);
	SceneCaptureComponentProfile->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

	// Don't show background
	SceneCaptureComponentProfile->ShowOnlyActors = { this };
}

// Called when the game starts or when spawned
void ACharacterSelector::BeginPlay()
{
	Super::BeginPlay();

	// Spawn ClothHair Class.
	if (ClothHairClass)
	{
		ClothHair = GetWorld()->SpawnActor<AClothPartsBase>(ClothHairClass);

		const USkeletalMeshSocket* HairSocket = MeshComponent->GetSocketByName("HairSocket");
		if (!HairSocket)
			return;

		// Attach Weapon to HairSocket and set Owner.
		HairSocket->AttachActor(ClothHair, MeshComponent);
		ClothHair->SetOwner(this);

		// Setup Collision Profile
		ClothHair->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponHero"));
		
		SceneCaptureComponent->ShowOnlyActors.Add(ClothHair);
		SceneCaptureComponentProfile->ShowOnlyActors.Add(ClothHair);
	}
}

// Called every frame
void ACharacterSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
