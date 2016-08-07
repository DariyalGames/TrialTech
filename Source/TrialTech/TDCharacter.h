// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "TDCharacter.generated.h"




UCLASS()
class TRIALTECH_API ATDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDCharacter(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|ThirdPerson")
	USpringArmComponent* TPCameraBoomComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|ThirdPerson")
	UCameraComponent* TPCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|SideScroller")
	USpringArmComponent* SSCameraBoomComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|SideScroller")
	UCameraComponent* SSCameraComponent;

	void SwitchToThirdPerson();
	void SwitchToSideScroller();

	UFUNCTION()
	void FireWeapon();

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	TSubclassOf<class AWeapon> WeaponSpawn;

	AWeapon* CurrentWeapon;
};
