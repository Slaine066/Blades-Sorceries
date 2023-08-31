// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventorySlot.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Styling/SlateBrush.h"

UPlayerItemInventorySlot::UPlayerItemInventorySlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{	
}

void UPlayerItemInventorySlot::SetItemImagePath(FString Path)
{
	ItemImagePath = Path;
}

void UPlayerItemInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetTree)
	{
		CanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("CanvasWidget"));
		CanvasPanel->RenderOpacity = 1.f;

		WidgetTree->RootWidget = CanvasPanel;

		FString CellPath = FString("'/Game/Portfolio_0/UI/Item_InventorySlot_Screen/Resource/Cell.Cell'");
		UTexture2D* CellTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *CellPath));

		ImageBg = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Image_ItemSlot"));
		ImageBg->SetBrushFromTexture(CellTexture);
		ImageBg->SetDesiredSizeOverride(FVector2D(50.f, 50.f));
		ImageBg->SetVisibility(ESlateVisibility::Visible);

		UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ItemImagePath));

		ImageItem = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Image_ItemImage"));
		//Change ItemImage
		ImageItem->SetBrushFromTexture(ItemTexture);
		ImageItem->SetDesiredSizeOverride(FVector2D(50.f, 50.f));
		ImageItem->SetVisibility(ESlateVisibility::Visible);

		UCanvasPanelSlot* CanvasImageBgSlot = CanvasPanel->AddChildToCanvas(ImageBg);
		CanvasImageBgSlot->SetSize(FVector2D(50.f, 50.f));

		UCanvasPanelSlot* CanvasImageItemSlot = CanvasPanel->AddChildToCanvas(ImageItem);
		CanvasImageItemSlot->SetSize(FVector2D(50.f, 50.f));
	}	
}
