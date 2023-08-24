// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Hero/HeroArcher.h"
#include "Actors/WeaponBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include <EnhancedInputComponent.h>
#include "AnimInstances/Hero/AnimInstanceHeroArcher.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

AHeroArcher::AHeroArcher()
	: bIsAttack(false)
{
}

void AHeroArcher::OnNormalAttack()
{
	bIsAttack = true;
}



void AHeroArcher::BeginPlay()
{
	Super::BeginPlay();

	SetWeapon();

}

void AHeroArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMousePos();

	if (bShoot == true)
	{
		fShootTime += DeltaTime;
	}


 	if (fShootTime >= 1.f)
	{
		bShoot = false;
		fShootTime = 0.f;
	}


}

void AHeroArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// NormallAttack
			EnhancedInputComponent->BindAction(NormalAttackArcherAction, ETriggerEvent::Triggered, this, &AHeroArcher::NormalAttackFunc);

	}

}

void AHeroArcher::SetWeapon()
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

void AHeroArcher::NormalAttackFunc(const FInputActionValue& Value)
{
	if (bShoot == false)
	{
		PlayAnimMontage(NormalAttack);
		ArrowFire();
	}
}

void AHeroArcher::UpdateMousePos()
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

void AHeroArcher::ArrowFire()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	FVector MouseWorldLocation, MouseWorldDirection;
	PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

	FHitResult HitResult;
	Temp = GetActorLocation();

	FVector TTfdadf = Temp;
	FVector StartLocation = MouseWorldLocation;
	FVector EndLocation = MouseWorldLocation + MouseWorldDirection * 5000.f;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // 이 액터를 무시하도록 설정하거나 필요에 따라 추가 설정

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility, // 라인 트레이스에 사용할 채널 설정 (다른 채널로 변경 가능)
		CollisionParams
	);
	
	if (bHit)
	{
		bShoot = true;
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.0f);
	
		// 라인 트레이스 충돌이 감지되었을 때 수행할 작업
		// HitResult 변수를 사용하여 충돌한 정보에 접근 가능

		FVector NewLocation = HitResult.ImpactPoint;
		//SetActorLocation(NewLocation);

		FVector SpawnLocation = GetActorLocation(); // 원하는 위치 설정
		FRotator SpawnRotation = GetActorRotation(); // 원하는 회전 설정
		FActorSpawnParameters SpawnParams;
		AArrowProjectile* Projectile = GetWorld()->SpawnActor<AArrowProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (Projectile)
		{
			FVector ShootDir = NewLocation.GetSafeNormal() - GetActorLocation().GetSafeNormal();
			ShootDir.Z = 0.f;

			//MouseWorldDirection.Z = 0.f;
			//FQuat RotationDelta = FQuat::FindBetweenVectors(GetActorForwardVector(), MouseWorldDirection);
			//AddActorLocalRotation(RotationDelta);

			FVector ForwardVector = NewLocation - GetActorLocation();
			ForwardVector.Z = 0.0f; // Keep the rotation in the horizontal plane

			FRotator NewRotation = ForwardVector.Rotation();
			SetActorRotation(NewRotation);


			

			// 생성된 프로젝타일 객체 사용
			Projectile->FireArrowDirection(GetActorForwardVector());
		}

	}



}

void AHeroArcher::Fire(FVector vDirection)
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

void AHeroArcher::HandlePicking()
{

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	FVector MouseWorldLocation, MouseWorldDirection;
	PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

	FHitResult HitResult;
	Temp = GetActorLocation();

	FVector TTfdadf = Temp;
	FVector StartLocation = MouseWorldLocation;
	FVector EndLocation = MouseWorldLocation + MouseWorldDirection * 5000.f;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // 이 액터를 무시하도록 설정하거나 필요에 따라 추가 설정




	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility, // 라인 트레이스에 사용할 채널 설정 (다른 채널로 변경 가능)
		CollisionParams
	);

	if (bHit)
	{
		// 라인 트레이스 충돌이 감지되었을 때 수행할 작업
		// HitResult 변수를 사용하여 충돌한 정보에 접근 가능
		
		FVector NewLocation = HitResult.ImpactPoint;
		//SetActorLocation(NewLocation);

		FVector SpawnLocation = GetActorLocation(); // 원하는 위치 설정
		FRotator SpawnRotation = GetActorRotation(); // 원하는 회전 설정
		FActorSpawnParameters SpawnParams;
		AArrowProjectile* Projectile = GetWorld()->SpawnActor<AArrowProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (Projectile)
		{
			FVector ShootDir = NewLocation.GetSafeNormal() - GetActorLocation().GetSafeNormal();
			ShootDir.Z = 0.f;

			// 생성된 프로젝타일 객체 사용
			Projectile->FireArrowDirection(ShootDir);
		}

	}

	//if (Controller != nullptr)
//{
//	FVector CurrentPosition = GetActorLocation();
//	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
//	FVector WorldLocation, WorldDirection;
//
//	APlayerController* PlayerController = Cast<APlayerController>(GetController());
//	
//	

//	//UGameplayStatics::DeprojectScreenToWorld

//	if (PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection))
//	{
//		FVector Direction = CurrentPosition - WorldLocation;
//		FVector RealDir = Direction;
//		Direction.Z = 0.0f; // Z 방향 회전은 제한합니다.

//		//// 보간된 방향 벡터를 얻습니다.
//		//FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
//		//FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 45.f);

//		//// 캐릭터 회전을 보간된 회전으로 설정합니다.
//		//SetActorRotation(NewRotation);

//		FQuat RotationDelta = FQuat::FindBetweenVectors(GetActorForwardVector(), Direction);
//		AddActorLocalRotation(RotationDelta);

//		UE_LOG(LogTemp, Log, TEXT("Rotate"));
//		UE_LOG(LogTemp, Log, TEXT("Rotate"));
//		UE_LOG(LogTemp, Log, TEXT("Rotate"));

//		//Fire(RealDir);

//		HandlePicking();
//	}

//	// Add yaw and pitch input to Controller
//	//AddControllerYawInput();
//	
//}

}


