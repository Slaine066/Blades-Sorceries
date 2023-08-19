// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickupable.generated.h"

UENUM()
enum class EPickupableType { EXPERIENCE_SMALL, EXPERIENCE_MEDIUM, EXPERIENCE_BIG, POTION, CHEST };

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
	EPickupableType Get_Type() { return Type; }
	int Get_GivenExperience() { return GivenExperience; }
	int Get_GivenHealth() { return GivenHealth; }
	void Set_Hero(AActor* _Hero) { Hero = _Hero; }

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
	* Variables
	*/
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EPickupableType Type;
	UPROPERTY(EditDefaultsOnly, Category = "Experience")
	int GivenExperience;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int GivenHealth;

	AActor* Hero = nullptr;
};
