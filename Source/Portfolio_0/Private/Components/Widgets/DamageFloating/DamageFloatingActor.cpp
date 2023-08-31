// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/DamageFloating/DamageFloatingActor.h"
#include "Components/Widgets/DamageFloating/DamageFloatingUI.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADamageFloatingActor::ADamageFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DamageFloatingSceneComponent"));
		SetRootComponent(RootComponent);
	}

	if (!DamageFloatingMeshComponent)
	{	
		DamageFloatingMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DamageFloatingMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/PolygonDungeons/Meshes/FX/Cube.Cube'"));
		if (Mesh.Succeeded())
		{
			DamageFloatingMeshComponent->SetStaticMesh(Mesh.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/PolygonDungeons/Materials/Misc/Mat_FX_Fire.Mat_FX_Fire'"));
		if (Material.Succeeded())
		{
			DamageFloatingMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, DamageFloatingMeshComponent);
		}

		DamageFloatingMeshComponent->SetMaterial(0, DamageFloatingMaterialInstance);
		DamageFloatingMeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
		DamageFloatingMeshComponent->SetupAttachment(RootComponent);
		DamageFloatingMeshComponent->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
		DamageFloatingMeshComponent->SetEnableGravity(false);
		DamageFloatingMeshComponent->SetVisibility(false);
	}

	DamageFloatingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageFloating"));
	DamageFloatingWidgetComponent->SetupAttachment(DamageFloatingMeshComponent);
	DamageFloatingWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	DamageFloatingWidgetComponent->SetDrawAtDesiredSize(true);

	static ConstructorHelpers::FClassFinder<UDamageFloatingUI>UI_DamageFloating_C(TEXT("'/Game/Portfolio_0/UI/FloatingDamage/WBP_FloatingDamage.WBP_FloatingDamage_C'"));
	if (UI_DamageFloating_C.Succeeded())
	{
		DamageFloatingWidgetComponent->SetWidgetClass(UI_DamageFloating_C.Class);
	}	

	SetLifeSpan(3.f);
}

void ADamageFloatingActor::SetInfoToSpawn(float fDamage, float fSpeed, FVector Direction)
{
	iDamage = fDamage;	
	Speed = fSpeed;
	SpawnDirection = Direction.GetSafeNormal();
}

void ADamageFloatingActor::SetToWidgetInfo(FLinearColor RGBAColorValue, int iFontSizeValue, int iOutlineSizeValue, FLinearColor OutLineColor)
{
	//DamageFloatingWidgetComponent->AddWorldOffset(FVector(0.f, 0.f, -300.f));

	UDamageFloatingUI* DamageFloatingWidget = Cast<UDamageFloatingUI>(DamageFloatingWidgetComponent->GetUserWidgetObject());

	if (DamageFloatingWidget)
	{
		DamageFloatingWidget->SetInfo(iDamage, RGBAColorValue, iFontSizeValue, iOutlineSizeValue, OutLineColor);		
	}
}

// Called when the game starts or when spawned
void ADamageFloatingActor::BeginPlay()
{
	Super::BeginPlay();	
}

void ADamageFloatingActor::BeginDestroy()
{
	Super::BeginDestroy();
}

// Called every frame
void ADamageFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*DamageFloatingMeshComponent->AddImpulse(FVector(0.f, 0.f, Speed) * DeltaTime);*/

	AddActorWorldOffset(FVector(0.f, 0.f, Speed) * DeltaTime);
}