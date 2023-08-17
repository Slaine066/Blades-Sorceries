// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Crosshair.generated.h"


/**
 * 
 */
UCLASS()
class PORTFOLIO_0_API ACrosshair : public AHUD
{
	GENERATED_BODY()

public:
	ACrosshair();


	FVector2D GetCrosshairPos() const { return m_vCrosshairPos; }


public:
	// HUD에 대한 드로우콜
	virtual void DrawHUD() override;


	
protected:
	// 화면 중앙에 그려질 것이다.
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairTexture;

private:
	FVector2D m_vCrosshairPos;
	
};
