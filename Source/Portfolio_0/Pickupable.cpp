// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickupable.h"
#include "CharacterHero.h"

// Sets default values
APickupable::APickupable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupable::BeginPlay()
{
	Super::BeginPlay();
	
	// Overlap Delegates
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupable::OnOverlapBegin);
}

// Called every frame
void APickupable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Type == EPickupableType::EXPERIENCE_SMALL || Type == EPickupableType::EXPERIENCE_MEDIUM || Type == EPickupableType::EXPERIENCE_BIG)
	{
		/* If in Hero's PickupRange move towards Hero. */
		// TODO:
	}
}

void APickupable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterHero* Hero = Cast<ACharacterHero>(OtherActor);
	
	if (Hero)
		Hero->OnPickup(Type);
}

