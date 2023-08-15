// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingDamageWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class PORTFOLIO_0_API UFloatingDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UTextBlock* GetDamageText() { return DamageText; }

	void ConvertDamageToText(float Damage);

protected:

	/* Methods */
	/* when create widget Call only one */
	virtual void NativeOnInitialized() override;		
	virtual void NativePreConstruct() override;
	/* before the call AddToViewport, Different to 'NativeOnOnitialized' it will be callup the every 'Viewport Add' time  */
	virtual void NativeConstruct() override;
	/* when it call 'RemoveFromParent' it is callup */
	virtual void NativeDestruct() override;

	/* Variables */

private:
	/* Methods */

	/* Variables */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText;

	
};
