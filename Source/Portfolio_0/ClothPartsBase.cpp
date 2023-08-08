// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothPartsBase.h"
#include "CharacterBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AClothPartsBase::AClothPartsBase()
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
void AClothPartsBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Overlap Delegates
	//MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AClothPartsBase::OnOverlapBegin);
}

// Called every frame
void AClothPartsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AClothPartsBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

