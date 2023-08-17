// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHeroArcher.h"
#include "WeaponBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include <EnhancedInputComponent.h>
#include "AnimInstanceHeroArcher.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"




ACharacterHeroArcher::ACharacterHeroArcher()
	: bIsAttack(false)
{
}

void ACharacterHeroArcher::OnNormalAttack()
{
	bIsAttack = true;
}



void ACharacterHeroArcher::BeginPlay()
{
	Super::BeginPlay();

	SetWeapon();

}

void ACharacterHeroArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMousePos();

}

void ACharacterHeroArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// NormallAttack
		EnhancedInputComponent->BindAction(NormalAttackArcherAction, ETriggerEvent::Triggered, this, &ACharacterHeroArcher::NormalAttackFunc);

	}

}

void ACharacterHeroArcher::SetWeapon()
{
	if (WeaponClassLeft)
	{
		WeaponLeft = GetWorld()->SpawnActor<AWeaponBase>(WeaponClassLeft);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("WeaponSocketL");
		if (!WeaponSocket)
			return;

		// Retrieve WeaponSocket.
		if (WeaponSocket)
		{
			// Attach Weapon to WeaponSocket and set Owner.
			WeaponSocket->AttachActor(WeaponLeft, GetMesh());
			WeaponLeft->SetOwner(this);

			// Setup Collision Profile
			WeaponLeft->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponHero"));
		}
	}
}

void ACharacterHeroArcher::NormalAttackFunc(const FInputActionValue& Value)
{
	PlayAnimMontage(NormalAttack);
	ArrowFire();
}

void ACharacterHeroArcher::UpdateMousePos()
{
	m_vMousePosition = FVector::ZeroVector;
	float fMouseX = 0.f;
	float fMouseY = 0.f;

	

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (PlayerController->GetMousePosition(fMouseX, fMouseY))
		{
			// 캔버스 중심을 찾는다
			m_vMousePosition = FVector(fMouseX, fMouseY, 0.f);

			FVector2D ScreenCenter = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()) / 2.f;
			FVector2D NewCrosshairLocation = ScreenCenter +  FVector2D(fMouseX, fMouseY);

			m_vMousePosition.X = NewCrosshairLocation.X;
			m_vMousePosition.Y = NewCrosshairLocation.Y;
		}
	}
	
	//if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	//{
	//	if (PlayerController->GetMousePosition(fMouseX, fMouseY))
	//	{
	//		// 캔버스 중심을 찾는다
	//		m_vMousePosition = FVector(fMouseX, fMouseY, 0.f);
	//	}
	//}
}

void ACharacterHeroArcher::ArrowFire()
{
	if (Controller != nullptr)
	{
		FVector CurrentPosition = GetActorLocation();
		FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		FVector WorldLocation, WorldDirection;
	
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		
		//UGameplayStatics::DeprojectScreenToWorld

		if (PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection))
		{
			FVector Direction = CurrentPosition - WorldLocation;
			FVector RealDir = Direction;
			Direction.Z = 0.0f; // Z 방향 회전은 제한합니다.

			//// 보간된 방향 벡터를 얻습니다.
			//FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
			//FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 45.f);

			//// 캐릭터 회전을 보간된 회전으로 설정합니다.
			//SetActorRotation(NewRotation);

			FQuat RotationDelta = FQuat::FindBetweenVectors(GetActorForwardVector(), Direction);
			AddActorLocalRotation(RotationDelta);

			UE_LOG(LogTemp, Log, TEXT("Rotate"));
			UE_LOG(LogTemp, Log, TEXT("Rotate"));
			UE_LOG(LogTemp, Log, TEXT("Rotate"));

			Fire(RealDir);

			//HandlePicking();
		}

		// Add yaw and pitch input to Controller
		//AddControllerYawInput();
		
	}
}

void ACharacterHeroArcher::Fire(FVector vDirection)
{
	if (ProjectileClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Fire"));
		UE_LOG(LogTemp, Log, TEXT("Fire"));
		UE_LOG(LogTemp, Log, TEXT("Fire"));


		FVector ArcherLocation = GetActorLocation();
		FRotator ArcherRotation = GetActorRotation();

		// Set MagicMuzzle Offset from camera space to world space
		FVector MuzzleLocation = ArcherLocation + FTransform(ArcherRotation).TransformVector(MuzzleOffset);

		//Skew the aim to be slightly upwards
		FRotator MuzzleRotation = ArcherRotation;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle
			AArrowProjectile* Projectile = World->SpawnActor<AArrowProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			//if (Projectile)
			//{
			//	FVector CurrentPos = GetActorLocation();
			//	FVector PickPos = vDirection;

			//	FVector Dir = PickPos - CurrentPos;

			//	
			//	Projectile->FireArrowDirection(Dir);
			//}

			if (Projectile)
			{
				// Set the projectiles's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();

				

				Projectile->FireArrowDirection(LaunchDirection);
			}
		}
	}
	else
		UE_LOG(LogTemp, Log, TEXT("Fuck"));



}

void ACharacterHeroArcher::HandlePicking()
{
	UE_LOG(LogTemp, Log, TEXT("HandlePicking"));

	FVector StartLocation;
	FRotator CamLot;
	FVector EndLocation;

	FHitResult HitResult;


	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		
		PlayerController->GetPlayerViewPoint(StartLocation, CamLot);

		EndLocation = StartLocation + GetControlRotation().Vector() * 100.f;

		FCollisionQueryParams CollisionParams;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

		if (bHit)
		{
			AActor* HitActor = HitResult.GetActor();
			if(HitActor)
			{
				Fire(HitActor->GetActorLocation());
			}
		}
	}
}


