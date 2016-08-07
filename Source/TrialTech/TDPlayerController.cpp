// Fill out your copyright notice in the Description page of Project Settings.

#include "TrialTech.h"
#include "TDPlayerController.h"
#include "TDCharacter.h"
#include "TDPlayerCameraManager.h"


ATDPlayerController::ATDPlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ATDPlayerCameraManager::StaticClass();
}

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATDPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATDPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &ATDPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &ATDPlayerController::LookUp);

	InputComponent->BindAction("SwitchControl", IE_Pressed, this, &ATDPlayerController::SwitchControlScheme);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATDPlayerController::FireWeapon);

	CurrentControlScheme = EControlScheme::CS_ThirdPerson;
}


void ATDPlayerController::MoveForward(float Val)
{
	if (CurrentControlScheme == EControlScheme::CS_SideScroller)
		return;

	ATDCharacter* pawn = Cast<ATDCharacter>(GetCharacter());

	if (pawn && Val != 0.f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ATDTPPlayerController::MoveForward:>Cast<ATDCharacter>(GetControlledPawn()) success");
		const bool bLimitRotation = (pawn->GetCharacterMovement()->IsMovingOnGround() || pawn->GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? pawn->GetActorRotation() : GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		pawn->AddMovementInput(Direction, Val);
	}
}

void ATDPlayerController::MoveRight(float Val)
{


	ATDCharacter* pawn = Cast<ATDCharacter>(GetCharacter());

	if (pawn && Val != 0.f)
	{
		if (CurrentControlScheme == EControlScheme::CS_SideScroller)
		{
			//const bool bLimitRotation = (pawn->GetCharacterMovement()->IsMovingOnGround() || pawn->GetCharacterMovement()->IsFalling());
			//const FRotator Rotation = GetControlRotation();
			//const FRotator NR = FRotator()
			//const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

			pawn->AddMovementInput(FVector(1.f, 0, 0), Val);
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ATDTPPlayerController::MoveRight:>Cast<ATDCharacter>(GetControlledPawn()) success");
			const FRotator Rotation = pawn->GetActorRotation();
			const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

			pawn->AddMovementInput(Direction, Val);
		}
	}
}


void ATDPlayerController::Turn(float Val)
{
	if (CurrentControlScheme == EControlScheme::CS_SideScroller)
		return;

	ATDCharacter* pawn = Cast<ATDCharacter>(GetCharacter());

	if (pawn && Val != 0.f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ATDTPPlayerController::Turn:>Cast<ATDCharacter>(GetControlledPawn()) success");
		pawn->AddControllerYawInput(Val);
	}
}

void ATDPlayerController::LookUp(float Val)
{
	if (CurrentControlScheme == EControlScheme::CS_SideScroller)
		return;

	ATDCharacter* pawn = Cast<ATDCharacter>(GetCharacter());

	if (pawn && Val != 0.f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ATDTPPlayerController::LookUp:>Cast<ATDCharacter>(GetControlledPawn()) success");
		pawn->AddControllerPitchInput(Val);
	}
}

void ATDPlayerController::FireWeapon()
{
	ATDCharacter* pawn = Cast<ATDCharacter>(GetCharacter());

	if (pawn)
	{
		pawn->FireWeapon();
	}
}

void ATDPlayerController::SwitchControlScheme()
{
	switch (CurrentControlScheme)
	{
	case EControlScheme::CS_SideScroller:
		SwitchToThirdPerson();
		break;
	case EControlScheme::CS_ThirdPerson:
		SwitchToSideScroller();
		break;
	default:
		break;
	}
}


void ATDPlayerController::SwitchToThirdPerson()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "ThirdPerson");
	CurrentControlScheme = EControlScheme::CS_ThirdPerson;
	
	ATDCharacter* pawn = Cast<ATDCharacter>(GetCharacter());

	if (pawn)
	{
		pawn->SwitchToThirdPerson();
	}
}

void ATDPlayerController::SwitchToSideScroller()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "SideScroller");
	CurrentControlScheme = EControlScheme::CS_SideScroller;

	ATDCharacter* pawn = Cast<ATDCharacter>(GetCharacter());

	if (pawn)
	{
		pawn->SwitchToSideScroller();

	}
}

