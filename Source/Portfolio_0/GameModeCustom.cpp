// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModeCustom.h"
#include "CharacterMob.h"
#include "Kismet/GameplayStatics.h"
#include "MobGoblin.h"

void AGameModeCustom::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AGameModeCustom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* "MobCountLimit" changes based on the GameTimer. */
	CheckGameTimer();
}

void AGameModeCustom::CheckGameTimer()
{
	AGameStateCustom* GameStateCustom = Cast<AGameStateCustom>(GameState);
	if (!GameStateCustom)
		return;

	FGameTimer GameTimer = GameStateCustom->Get_GameTimer();
	switch (GameTimer.Minutes)
	{
	case 0:
		MobCountLimit = 10;
		MobSpawnType = { EMobType::SKELETON_SLAVE };
		break;
	case 1:
		MobCountLimit = 20;
		MobSpawnType = { EMobType::SKELETON_SLAVE, EMobType::SKELETON_SOLDIER };
		break;
	case 2:
		MobCountLimit = 30;
		BossSpawnType = EBossType::SKELETON_KNIGHT;
		break;
	case 3:
		MobCountLimit = 40;
		MobSpawnType = { EMobType::GOBLIN };
		break;
	case 4:
		MobCountLimit = 50;
		MobSpawnType = { EMobType::GOBLIN, EMobType::GOBLIN_WARRIOR };
		break;
	case 5:
		MobCountLimit = 60;
		MobSpawnType = { EMobType::GOBLIN, EMobType::GOBLIN_WARRIOR, EMobType::GOBLIN_SHAMAN };
		break;
	case 6:
		MobCountLimit = 70;
		BossSpawnType = EBossType::GOBLIN_WAR_CHIEF;
		break;
	case 7:
		MobCountLimit = 80;
		MobSpawnType = { EMobType::GOLEM };
		break;
	case 8:
		MobCountLimit = 90;
		BossSpawnType = EBossType::LAVA_GOLEM;
		break;
	case 9:
		MobCountLimit = 100;
		MobSpawnType = { EMobType::GHOST };
		break;
	case 10:
		Despawn();
		BossSpawnType = EBossType::DEMON;
		break;
	}

	Spawn(GameTimer);
}

void AGameModeCustom::Spawn(FGameTimer GameTimer)
{
	AGameStateCustom* GameStateCustom = Cast<AGameStateCustom>(GameState);
	if (!GameStateCustom)
		return;

	/* Spawn Mobs up to "MobCountLimit". */
	if (GameStateCustom->Get_MobCount() < MobCountLimit) /* Could have used a while loop. But by using an if statement a single Mob gets spawned every Tick() (which is better in my opinion). */
	{
		/* Randomly choose a MobType and spawn it. */
		EMobType MobType = MobSpawnType[FMath::RandRange(1, MobSpawnType.Num()) - 1];

		FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation();

		FVector SpawnLocation = Get_RandomSpawnLocation(PlayerLocation);

		FVector DirectionToPlayer = PlayerLocation - SpawnLocation;
		DirectionToPlayer.Normalize();

		FRotator SpawnRotation = DirectionToPlayer.Rotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AMobGoblin* Mob = GetWorld()->SpawnActor<AMobGoblin>(SpawnableMobs[MobType], SpawnLocation, SpawnRotation, SpawnParams);
	
		if (Mob)
			GameStateCustom->IncreaseMobCount();
	}

	/* Bosses Spawn once at a specific Time. */
	if (GameTimer.Minutes > LastBossSpawnTimer.Minutes)
	{
		switch (BossSpawnType)
		{
		case EBossType::SKELETON_KNIGHT:
			/* */
			break;
		case EBossType::GOBLIN_WAR_CHIEF:
			/* */
			break;
		case EBossType::LAVA_GOLEM:
			/* */
			break;
		case EBossType::DEMON:
			/* */
			break;
		}

		LastBossSpawnTimer = GameTimer;
	}
}

void AGameModeCustom::Despawn()
{
	/* Despawn all Mobs before Final Boss appears. */
}

FVector AGameModeCustom::Get_RandomSpawnLocation(FVector PlayerLocation)
{
	FRandomStream RandomStream(FMath::Rand()); // Seed

	float RandomAngle = FMath::DegreesToRadians(RandomStream.FRandRange(0.0f, 360.0f));
	float RandomDistance = RandomStream.FRandRange(1000.f, 1500.f);

	FVector RandomOffset = FVector(RandomDistance * FMath::Cos(RandomAngle), RandomDistance * FMath::Sin(RandomAngle), 0.0f);
	FVector RandomLocation = PlayerLocation + RandomOffset;

	// Ray-Tracing downward to find the Terrain Surface.
	FHitResult HitResult;
	FVector StartLocation = RandomLocation + FVector(0.0f, 0.0f, 1000.0f);
	FVector EndLocation = RandomLocation - FVector(0.0f, 0.0f, 1000.0f);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		RandomLocation = HitResult.ImpactPoint;
	}

	return RandomLocation;
}

FRotator AGameModeCustom::Get_SpawnRotation()
{
	return FRotator();
}
