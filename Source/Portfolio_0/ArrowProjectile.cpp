// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowProjectile.h"

// Sets default values
AArrowProjectile::AArrowProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  
    UE_LOG(LogTemp, Log, TEXT("Create FireArrowDirection"));

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
    }

    if (!CollisionComponent)
    {
        // Use a sphere as a simple collision representation.
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // Set the sphere's collision radius.
        CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
        // Use this component to drive this projectile's movement.
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = 2000.f;
        ProjectileMovementComponent->MaxSpeed = 2000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = false;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

    if (!ProjectileMeshComponent)
    {
        ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
        static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/PolygonElven/Models/Weapons/SM_Wep_Arrow_01.SM_Wep_Arrow_01'"));
        if (Mesh.Succeeded())
        {
            ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
        }

        static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/PolygonElven/Materials/Alts/M_PolygonElven_Mat_01_A.M_PolygonElven_Mat_01_A'"));
        if (Material.Succeeded())
        {
            ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
        }
        ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
        ProjectileMeshComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
        ProjectileMeshComponent->SetupAttachment(RootComponent);
        FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
        ProjectileMeshComponent->SetWorldRotation(NewRotation);

    }

 
   

    
}

// Called when the game starts or when spawned
void AArrowProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrowProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArrowProjectile::FireArrowDirection(const FVector& vDirection)
{
    UE_LOG(LogTemp, Log, TEXT("FireArrowDirection"));
    UE_LOG(LogTemp, Log, TEXT("FireArrowDirection"));
    UE_LOG(LogTemp, Log, TEXT("FireArrowDirection"));
    ProjectileMovementComponent->Velocity = vDirection * ProjectileMovementComponent->InitialSpeed;
}

