// Fill out your copyright notice in the Description page of Project Settings.

#include "TrialTech.h"
#include "TrialTechGameMode.h"
#include "TDCharacter.h"
#include "TDPlayerController.h"



ATrialTechGameMode::ATrialTechGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<ATDCharacter> MyPawnClass(TEXT("Pawn'/Game/Blueprints/Character/BP_TDCharacter.BP_TDCharacter_C'"));
	if (MyPawnClass.Class != NULL)
	{
		DefaultPawnClass = MyPawnClass.Class;
	}

	PlayerControllerClass = ATDPlayerController::StaticClass();
}
