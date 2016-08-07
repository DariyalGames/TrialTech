// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "TDPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class TRIALTECH_API ATDPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()



	ATDPlayerCameraManager(const class FObjectInitializer& ObjectInitializer);
	
	virtual void UpdateCamera(float DeltaTime) override;
	
public:
	float NormalFOV;
	float TargetingFOV;
};
