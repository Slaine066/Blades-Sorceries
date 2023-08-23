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
	// HUD�� ���� ��ο���
	virtual void DrawHUD() override;


	
protected:
	// ȭ�� �߾ӿ� �׷��� ���̴�.
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairTexture;

private:
	FVector2D m_vCrosshairPos;
	
};
