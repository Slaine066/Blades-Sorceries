// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterSelector.generated.h"

class AClothPartsBase;

UCLASS()
class PORTFOLIO_0_API ACharacterSelector : public AActor
{
	GENERATED_BODY()

public:
	ACharacterSelector();

	/* Methods */

	/* Variables */

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Methods */

	/* Variables */
	UPROPERTY(EditDefaultsOnly, Category = "Cloth")
	TSubclassOf<AClothPartsBase> ClothHairClass;
	UPROPERTY()
	AClothPartsBase* ClothHair;

private:

	/* Methods */

	/* Variables */
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere)
	class USceneCaptureComponent2D* SceneCaptureComponent;
};
