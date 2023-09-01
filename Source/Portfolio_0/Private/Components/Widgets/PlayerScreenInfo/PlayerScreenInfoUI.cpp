// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerScreenInfoUI.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerHpWidget.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerExpWidget.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventory.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerScreenTimer.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerMobCount.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerStageInfo.h"



UPlayerScreenInfoUI::UPlayerScreenInfoUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerScreenInfoUI::SetPlayerHpInfo(FAttributes PlayerAttributes)
{
	Cast<UPlayerHpWidget>(HpBar)->UpdateHp(PlayerAttributes);
}

void UPlayerScreenInfoUI::SetPlayerExpInfo(FAttributes PlayerAttributes)
{
	Cast<UPlayerExpWidget>(ExpBar)->UpdateExp(PlayerAttributes);
}

void UPlayerScreenInfoUI::SetItemInventoryInfo(const TArray<class AItemBase*>& InventoryArray)
{
	Cast<UPlayerItemInventory>(ItemInventory)->UpdateInventoryInfo(InventoryArray);
}

void UPlayerScreenInfoUI::SetTimerInfo(int iMin, int iSec)
{
	Cast<UPlayerScreenTimer>(TimerInfo)->UpdateTime(iMin, iSec);
}

void UPlayerScreenInfoUI::SetMobCountInfo(int iMobCount)
{
	Cast<UPlayerMobCount>(MobCountInfo)->UpdateMobCount(iMobCount);
}

void UPlayerScreenInfoUI::SetStageInfo(int iStage)
{
	Cast<UPlayerStageInfo>(StageInfo)->UpdateStage(iStage);
}

void UPlayerScreenInfoUI::BindAttribute(FAttributes PlayerAttribute)
{
	Cast<UPlayerHpWidget>(HpBar)->BindCharacterAttribute(PlayerAttribute);
	Cast<UPlayerExpWidget>(ExpBar)->BindCharacterAttribute(PlayerAttribute);
}

void UPlayerScreenInfoUI::NativeConstruct()
{
	Super::NativeConstruct();

	//HpBar
	HpBar = Cast<UPlayerHpWidget>(GetWidgetFromName(TEXT("WBP_HealthBar")));
	if (nullptr == HpBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_HealthBar")));

	//ExpBar;
	ExpBar = Cast<UPlayerExpWidget>(GetWidgetFromName(TEXT("WBP_Exp_LevelBar")));
	if (nullptr == ExpBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_Exp_LevelBar")));

	//ItemInventory;
	ItemInventory = Cast<UPlayerItemInventory>(GetWidgetFromName(TEXT("WBP_Item_Inventory")));
	if (nullptr == ItemInventory)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_Item_Inventory")));

	//TimerInfo;
	TimerInfo = Cast<UPlayerScreenTimer>(GetWidgetFromName(TEXT("WBP_Screen_Timer")));
	if (nullptr == TimerInfo)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_Screen_Timer")));

	//MobCountInfo;
	MobCountInfo = Cast<UPlayerMobCount>(GetWidgetFromName(TEXT("WBP_Current_MobCount")));
	if (nullptr == MobCountInfo)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_Current_MobCount")));

	//StageInfo;
	StageInfo = Cast<UPlayerStageInfo>(GetWidgetFromName(TEXT("WBP_Current_Stage")));
	if (nullptr == StageInfo)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided Get Widget WBP_Current_Stage")));

}
