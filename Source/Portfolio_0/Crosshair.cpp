// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"
#include "Engine/Canvas.h"
#include "Blueprint/WidgetLayoutLibrary.h"


ACrosshair::ACrosshair()
{
}

void ACrosshair::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		// ĵ���� �߽��� ã�´�
		FVector2D MousePosition(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5);

		//FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		
		//MousePosition.X *= 0.5f;
		//MousePosition.Y *= 0.5f;

		// �ؽ�ó �߽��� ĵ���� �߽ɿ� �µ��� �ؽ�ó�� ũ�� ���� ��ŭ ������
		FVector2D CrossHairDrawPosition(MousePosition.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), MousePosition.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));
		//FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));
		
		m_vCrosshairPos = CrossHairDrawPosition;

		// �߽ɼ��� ���ؼ� ��ο�
		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;

		Canvas->DrawItem(TileItem);

	}



}
