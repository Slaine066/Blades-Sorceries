// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageNumberBase.generated.h"

class UWidgetCOmponent;

UCLASS()
class PORTFOLIO_0_API ADamageNumberBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageNumberBase();

	void SetDamage(const float Damage);
	int GetDamage() { return DamageNum; }

	// Cube Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "DamageFont")
	class UStaticMeshComponent* DamageMeshComponent;

	// Cube Material
	UPROPERTY(VisibleDefaultsOnly, Category = "DamageFont")
	UMaterialInstanceDynamic* DamageMaterialInstance;

	UPROPERTY(VisibleDefaultsOnly, Category = "DamageFont")
	class UWidgetComponent* WidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:	
	
	UPROPERTY(EditAnywhere, Category = "DamageFont")
	int DamageNum;



};
