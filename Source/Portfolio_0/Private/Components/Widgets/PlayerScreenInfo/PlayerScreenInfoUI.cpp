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

void UPlayerScreenInfoUI::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UPlayerHpWidget>(GetWidgetFromName(TEXT("WBP_HealthBar")));
	if (!HpBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_HealthBar")));

	ExpBar = Cast<UPlayerExpWidget>(GetWidgetFromName(TEXT("WBP_Exp_LevelBar")));
	if (!ExpBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Exp_LevelBar")));

	ItemInventory = Cast<UPlayerItemInventory>(GetWidgetFromName(TEXT("WBP_Item_Inventory")));
	if (!ItemInventory)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Item_Inventory")));

	TimerInfo = Cast<UPlayerScreenTimer>(GetWidgetFromName(TEXT("WBP_Screen_Timer")));
	if (!TimerInfo)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Screen_Timer")));

	MobCountInfo = Cast<UPlayerMobCount>(GetWidgetFromName(TEXT("WBP_Current_MobCount")));
	if (!MobCountInfo)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Current_MobCount")));

	StageInfo = Cast<UPlayerStageInfo>(GetWidgetFromName(TEXT("WBP_Current_Stage")));
	if (!StageInfo)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_Current_Stage")));

	SkillBar = Cast<UPlayerSkillBarUI>(GetWidgetFromName(TEXT("WBP_SkillBar")));
	if (!SkillBar)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faided to get Widget: WBP_SkillBar")));
}
