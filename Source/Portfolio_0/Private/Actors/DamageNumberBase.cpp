// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DamageNumberBase.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADamageNumberBase::ADamageNumberBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DamageFontSceneComponent"));
	}

	if (!DamageMeshComponent)
	{
		DamageMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DamageFontMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/PolygonDungeons/Meshes/FX/Cube.Cube'"));
		if (Mesh.Succeeded())
		{
			DamageMeshComponent->SetStaticMesh(Mesh.Object);
		}

		DamageMeshComponent->SetVisibility(true);

		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/PolygonDungeons/Materials/Misc/Mat_FX_Fire.Mat_FX_Fire'"));
		if (Material.Succeeded())
		{
			DamageMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, DamageMeshComponent);
		}
		DamageMeshComponent->SetMaterial(0, DamageMaterialInstance);
		DamageMeshComponent->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
		DamageMeshComponent->SetupAttachment(RootComponent);

		DamageMeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	}

	if (!WidgetComponent)
	{
		WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FloatingDamageComponent"));
	}

	InitialLifeSpan = 2.f;
}

void ADamageNumberBase::SetDamage(const float Damage)
{
	DamageNum = Damage;
}

// Called when the game starts or when spawned
void ADamageNumberBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageNumberBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(FVector(0.f, 0.f, 200.f * DeltaTime));
}

