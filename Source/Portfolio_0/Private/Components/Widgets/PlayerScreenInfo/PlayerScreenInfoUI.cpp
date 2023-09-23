// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Widgets/PlayerScreenInfo/PlayerScreenInfoUI.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerHpWidget.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerExpWidget.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerItemInventory.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerScreenTimer.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerMobCount.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerStageInfo.h"
#include "Components/Widgets/PlayerScreenInfo/PlayerSkillBarUI.h"
#include "SkillBase.h"

UPlayerScreenInfoUI::UPlayerScreenInfoUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerScreenInfoUI::InitAttributes(FAttributes PlayerAttribute)
{
	Cast<UPlayerHpWidget>(HpBar)->UpdateLevel(PlayerAttribute);
	Cast<UPlayerHpWidget>(HpBar)->UpdateHp(PlayerAttribute);
	Cast<UPlayerExpWidget>(ExpBar)->UpdateExp(PlayerAttribute);
}

void UPlayerScreenInfoUI::InitSkills(TArray<ASkillBase*> Skills)
{
	Cast<UPlayerSkillBarUI>(SkillBar)->UpdateSkills(Skills);
}

void UPlayerScreenInfoUI::ShowSkillBar()
{
	Cast<UPlayerSkillBarUI>(SkillBar)->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerScreenInfoUI::SetPlayerLevelInfo(FAttributes PlayerAttributes)
{
	Cast<UPlayerHpWidget>(HpBar)->UpdateLevel(PlayerAttributes);
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

void UPlayerScreenInfoUI::NativeConstruct()
{
	Super::NativeConstruct();

	TimerInfo = Cast<UPlayerScreenTimer>(GetWidgetFromName(TEXT("WBP_Screen_Timer")));
	if (!TimerInfo)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Screen_Timer")));

	HpBar = Cast<UPlayerHpWidget>(GetWidgetFromName(TEXT("WBP_HealthBar")));
	if (!HpBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_HealthBar")));

	ItemInventory = Cast<UPlayerItemInventory>(GetWidgetFromName(TEXT("WBP_Item_Inventory")));
	if (!ItemInventory)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Item_Inventory")));

	ExpBar = Cast<UPlayerExpWidget>(GetWidgetFromName(TEXT("WBP_Exp_LevelBar")));
	if (!ExpBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Exp_LevelBar")));

	SkillBar = Cast<UPlayerSkillBarUI>(GetWidgetFromName(TEXT("WBP_SkillBar")));
	if (!SkillBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_SkillBar")));
}
