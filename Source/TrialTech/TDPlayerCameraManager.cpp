// Fill out your copyright notice in the Description page of Project Settings.

#include "TrialTech.h"
#include "TDPlayerCameraManager.h"
#include "TDPlayerController.h"
//#include "TDCharacter.h"


ATDPlayerCameraManager::ATDPlayerCameraManager(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NormalFOV = 90.0f;
	TargetingFOV = 65.0f;

	ViewPitchMin = -80.0f;
	ViewPitchMax = 87.0f;
	bAlwaysApplyModifiers = true;
}

void ATDPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	ATDPlayerController* Control = Cast<ATDPlayerController>(PCOwner);
	//ATDCharacter* Char = Cast<ATDCharacter>(PCOwner->GetCharacter());

	/*if (Control && Char)
	{
		if (Control->BShiftingControlScheme)
		{
			switch (Control->CurrentControlScheme)
			{
			case EControlScheme::CS_ThirdPerson:
				Control->SetViewTargetWithBlend(Char->TPCameraComponent, 0.5f);
				break;
			case EControlScheme::CS_SideScroller:
			default:
				break;
			}
		}*/
		if (Control->CurrentControlScheme == EControlScheme::CS_ThirdPerson)
		{
			DefaultFOV = FMath::FInterpTo(DefaultFOV, NormalFOV, DeltaTime, 20.0f);
			SetFOV(DefaultFOV);
		}
	//}

	Super::UpdateCamera(DeltaTime);
}