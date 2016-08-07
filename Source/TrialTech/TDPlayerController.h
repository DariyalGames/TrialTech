// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TDPlayerController.generated.h"


UENUM(BlueprintType)
enum class EControlScheme : uint8
{
	CS_ThirdPerson	UMETA(DisplayName = "ThirdPerson"),
	CS_SideScroller	UMETA(DisplayName = "SideScroller")
};



/**
 * 
 */
UCLASS()
class TRIALTECH_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
	ATDPlayerController(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupInputComponent() override;

	void MoveForward(float Val);
	void MoveRight(float Val);
	void Turn(float Val);
	void LookUp(float Val);
	void FireWeapon();
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "ControlScheme")
	EControlScheme CurrentControlScheme;

	UFUNCTION(BlueprintCallable, Category="ControlScheme")
	void SwitchControlScheme();

	void SwitchToThirdPerson();
	void SwitchToSideScroller();

	bool BShiftingControlScheme;
};
