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
			// ĵ���� �߽��� ã�´�
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
	//		// ĵ���� �߽��� ã�´�
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
	CollisionParams.AddIgnoredActor(this); // �� ���͸� �����ϵ��� �����ϰų� �ʿ信 ���� �߰� ����

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility, // ���� Ʈ���̽��� ����� ä�� ���� (�ٸ� ä�η� ���� ����)
		CollisionParams
	);
	
	if (bHit)
	{
		bShoot = true;
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.0f);
	
		// ���� Ʈ���̽� �浹�� �����Ǿ��� �� ������ �۾�
		// HitResult ������ ����Ͽ� �浹�� ������ ���� ����

		FVector NewLocation = HitResult.ImpactPoint;
		//SetActorLocation(NewLocation);

		FVector SpawnLocation = GetActorLocation(); // ���ϴ� ��ġ ����
		FRotator SpawnRotation = GetActorRotation(); // ���ϴ� ȸ�� ����
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


			

			// ������ ������Ÿ�� ��ü ���
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
	CollisionParams.AddIgnoredActor(this); // �� ���͸� �����ϵ��� �����ϰų� �ʿ信 ���� �߰� ����




	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility, // ���� Ʈ���̽��� ����� ä�� ���� (�ٸ� ä�η� ���� ����)
		CollisionParams
	);

	if (bHit)
	{
		// ���� Ʈ���̽� �浹�� �����Ǿ��� �� ������ �۾�
		// HitResult ������ ����Ͽ� �浹�� ������ ���� ����
		
		FVector NewLocation = HitResult.ImpactPoint;
		//SetActorLocation(NewLocation);

		FVector SpawnLocation = GetActorLocation(); // ���ϴ� ��ġ ����
		FRotator SpawnRotation = GetActorRotation(); // ���ϴ� ȸ�� ����
		FActorSpawnParameters SpawnParams;
		AArrowProjectile* Projectile = GetWorld()->SpawnActor<AArrowProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (Projectile)
		{
			FVector ShootDir = NewLocation.GetSafeNormal() - GetActorLocation().GetSafeNormal();
			ShootDir.Z = 0.f;

			// ������ ������Ÿ�� ��ü ���
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
//		Direction.Z = 0.0f; // Z ���� ȸ���� �����մϴ�.

//		//// ������ ���� ���͸� ����ϴ�.
//		//FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
//		//FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 45.f);

//		//// ĳ���� ȸ���� ������ ȸ������ �����մϴ�.
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


