// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageFloatingActor.generated.h"

UCLASS()
class PORTFOLIO_0_API ADamageFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageFloatingActor();

	/* Methods */
	UFUNCTION()
	void SetInfo(float fDamage);

	/* Variables */

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;

	/* Methods */

	/* Variables */
	UPROPERTY(VisibleDefaultsOnly, Category = "Damage")
	class UStaticMeshComponent* DamageFloatingMeshComponent;

private:
	/* Methods */

	/* Variables */
	UPROPERTY()
	class UWidgetComponent* DamageFloatingWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Speed = 50.f;
};