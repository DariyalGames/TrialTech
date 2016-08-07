// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	PT_Bullet		UMETA(DisplayName = "Bullet"),
	PT_Spread		UMETA(DisplayName = "Spread"),
	PT_Projectile	UMETA(DisplayName = "Projectile"),
};


USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 ShotCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 MaxClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float WeaponRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float WeaponSpread;
};


UCLASS()
class TRIALTECH_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	UFUNCTION()
	void Fire();

	UFUNCTION()
	void InstaFire();

	UPROPERTY(EditAnywhere, Category = "Config")
	FWeaponData WeaponConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	EProjectileType ProjectileType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent *CollisionComponent;

protected:

	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TractTo) const;

	void ProcessInstantHit(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDirection, int32 RandomSeed, float ReticleSpread);
};


#define TRACE_WEAPON ECC_GameTraceChannel1