// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../GameStates/GameStateCustom.h"
#include "GameModeCustom.generated.h"

class ACharacterMob;

UENUM()
enum class EMobType { DEFAULT, SKELETON_SLAVE, SKELETON_SOLDIER, GOBLIN, GOBLIN_WARRIOR, GOBLIN_SHAMAN, GOLEM, GHOST };
UENUM()
enum class EBossType { DEFAULT, SKELETON_KNIGHT, GOBLIN_WAR_CHIEF, LAVA_GOLEM, DEMON };

UCLASS()
class PORTFOLIO_0_API AGameModeCustom : public AGameMode
{
	GENERATED_BODY()

public:
	/*
	* Methods Inherited
	*/
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*
	* Methods
	*/

	/*
	* Variables
	*/

protected:
	/*
	* Methods Inherited
	*/

	/*
	* Methods
	*/

	/*
	* Variables
	*/

private:
	/*
	* Methods
	*/
	void CheckGameTimer();
	void Spawn(FGameTimer GameTimer);
	void Despawn();
	FVector Get_RandomSpawnLocation(FVector PlayerLocation);

	/*
	* Variables
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Mob")
	TMap<EMobType, TSubclassOf<ACharacterMob>> SpawnableMobs;
	UPROPERTY(EditDefaultsOnly, Category = "Mob")
	TMap<EBossType, TSubclassOf<ACharacterMob>> SpawnableBossMobs;

	int MobCountLimit;
	TArray<EMobType> MobSpawnType = { EMobType::DEFAULT };
	EBossType BossSpawnType = EBossType::DEFAULT;
	FGameTimer LastBossSpawnTimer;
};
