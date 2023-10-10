// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceCustom.generated.h"

/**
 * 
 */

UCLASS()
class PORTFOLIO_0_API UGameInstanceCustom : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceCustom();

	/* Methods */
	TSubclassOf<class APawn> Get_SelectedCharacter() { return SelectableCharactersClass[SelectedCharacterIndex]; }
	void Set_SelectedCharacter(int CharacterIndex) { SelectedCharacterIndex = CharacterIndex; }

	/* Variables */

protected:
	/* Methods */

	/* Variables */
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APawn>> SelectableCharactersClass;

private:
	/* Methods */

	/* Variables */
	int SelectedCharacterIndex;
};
