// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickupable.generated.h"

UENUM()
enum class EPickupableType { DEFAULT, EXPERIENCE_SMALL, EXPERIENCE_MEDIUM, EXPERIENCE_BIG, POTION, CHEST };

UCLASS()
class PORTFOLIO_0_API APickupable : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupable();

	/*
	* Methods Inherited
	*/

	/*
	* Methods
	*/
	UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*
	* Methods
	*/

	/*
	* Variables
	*/

private:
	/*
	* Methods
	*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*
	* Variables
	*/
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EPickupableType Type = EPickupableType::DEFAULT;
};
