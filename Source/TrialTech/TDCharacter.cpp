// Fill out your copyright notice in the Description page of Project Settings.

#include "TrialTech.h"
#include "TDCharacter.h"
#include "Weapon.h"

// Sets default values
ATDCharacter::ATDCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TPCameraBoomComponent = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("TPCameraBoom"));
	TPCameraBoomComponent->SocketOffset = FVector(0, 35, 0);
	TPCameraBoomComponent->TargetOffset = FVector(0, 0, 55);
	TPCameraBoomComponent->bUsePawnControlRotation = true;
	TPCameraBoomComponent->SetupAttachment(GetRootComponent());

	TPCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("TPCamera"));
	TPCameraComponent->SetupAttachment(TPCameraBoomComponent);

	SSCameraBoomComponent = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SSCameraBoom"));
	SSCameraBoomComponent->SetupAttachment(GetRootComponent());
	SSCameraBoomComponent->bUsePawnControlRotation = false;
	SSCameraBoomComponent->TargetArmLength = 500.f;
	SSCameraBoomComponent->RelativeRotation = FRotator(0, -90.f, 0);

	SSCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SSCamera"));
	SSCameraComponent->SetupAttachment(SSCameraBoomComponent);

	
	GetCharacterMovement()->RotationRate = FRotator(0, 720.f, 0);
	

	static ConstructorHelpers::FObjectFinder<UBlueprint> WeaponBP(TEXT("Blueprint'/Game/Blueprints/Weapon/BP_Weapon.BP_Weapon'"));
	if (WeaponBP.Succeeded())
	{
		WeaponSpawn = (UClass*)WeaponBP.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	AWeapon* Spawnner = GetWorld()->SpawnActor<AWeapon>(WeaponSpawn, SpawnParams);
	if (Spawnner)
	{
		Spawnner->AttachRootComponentTo(GetMesh(), "Weapon_Socket", EAttachLocation::SnapToTarget);
		CurrentWeapon = Spawnner;
	}
}

// Called every frame
void ATDCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATDCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATDCharacter::SwitchToThirdPerson()
{
	SSCameraComponent->SetActive(false);
	TPCameraComponent->SetActive(true);
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ATDCharacter::SwitchToSideScroller()
{
	TPCameraComponent->SetActive(false);
	SSCameraComponent->SetActive(true);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ATDCharacter::FireWeapon()
{
	CurrentWeapon->Fire();
}
