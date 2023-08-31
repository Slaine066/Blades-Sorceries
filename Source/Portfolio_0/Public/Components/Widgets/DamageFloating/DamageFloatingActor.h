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
	// Sets default values for this actor's properties
	ADamageFloatingActor();

	UFUNCTION()
	void SetInfoToSpawn(float fDamage, float fSpeed = 100.f, FVector Direction = FVector(0.f, 0.f, 1.f));
	void SetToWidgetInfo(FLinearColor RGBAColorValue, int iFontSizeValue, int iOutlineSizeValue, FLinearColor OutLineColor);

	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// Floating Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "Damage")
	class UStaticMeshComponent* DamageFloatingMeshComponent;
	// Floating Material
	UPROPERTY(VisibleDefaultsOnly, Category = "Damage")
	UMaterialInstanceDynamic* DamageFloatingMaterialInstance;

private:	
	// Called every frame

	int		iDamage;
	FVector SpawnDirection;
	float Speed;

	UPROPERTY()
	class UWidgetComponent* DamageFloatingWidgetComponent;

};
