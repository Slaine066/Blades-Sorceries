// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHeroArcher.h"
#include "WeaponBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include <EnhancedInputComponent.h>
#include "AnimInstanceHeroArcher.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
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
			Direction.Z = 0.0f; // Z ���� ȸ���� �����մϴ�.

			//// ������ ���� ���͸� ����ϴ�.
			//FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
			//FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 45.f);

			//// ĳ���� ȸ���� ������ ȸ������ �����մϴ�.
			//SetActorRotation(NewRotation);

			FQuat RotationDelta = FQuat::FindBetweenVectors(GetActorForwardVector(), Direction);
			AddActorLocalRotation(RotationDelta);


		}

		// Add yaw and pitch input to Controller
		//AddControllerYawInput();
		
	}
}


