// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/WeaponBase.h"
#include "Actors/Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AWeaponBase::AWeaponBase()
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

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// Overlap Delegates
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* Character = Cast<ACharacterBase>(GetOwner());
	ACharacterBase* OtherCharacter = Cast<ACharacterBase>(OtherActor);
	
	if (!Character || !OtherCharacter)
		return;

	if (OtherCharacter->Get_IsDead())
		return;

	// Damage to the Overlapped Character
	if (Character->Get_CanDamage())
	{
		UGameplayStatics::ApplyDamage(OtherCharacter, Character->Get_Attributes().Damage, GetInstigatorController(), Character, DamageType);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticle, GetActorLocation());
		/*UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());*/
	}
}
