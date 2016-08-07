// Fill out your copyright notice in the Description page of Project Settings.

#include "TrialTech.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Collider"));
	RootComponent = CollisionComponent;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	WeaponMesh->SetupAttachment(CollisionComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWeapon::Fire()
{
	if (ProjectileType == EProjectileType::PT_Bullet)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Bullet"));
		InstaFire();
	}
	if (ProjectileType == EProjectileType::PT_Spread)
	{
		for (int32 i = 0; i < WeaponConfig.WeaponSpread; i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Spread"));
			InstaFire();
		}
	}
	if (ProjectileType == EProjectileType::PT_Projectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Projectile"));
	}
}

void AWeapon::InstaFire()
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream weaponRandomStream(RandomSeed);
	const float CurrentSpread = WeaponConfig.WeaponSpread;
	const float SpreadCone = FMath::DegreesToRadians(WeaponConfig.WeaponSpread*0.5);
	const FVector AimDir = WeaponMesh->GetSocketRotation("MuzzleFlashSocket").Vector();
	const FVector StartTrace = WeaponMesh->GetSocketLocation("MuzzleFlashSocket");
	const FVector ShootDir = weaponRandomStream.VRandCone(AimDir, SpreadCone, SpreadCone);
	const FVector EndTrace = StartTrace + ShootDir * WeaponConfig.WeaponRange;
	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);

	ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);
}

FHitResult AWeapon::WeaponTrace(const FVector & TraceFrom, const FVector & TraceTo) const
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));

	FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.AddIgnoredActor(this);

	FHitResult Hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, TRACE_WEAPON, TraceParams);

	return Hit;
}

void AWeapon::ProcessInstantHit(const FHitResult & Impact, const FVector & Origin, const FVector & ShootDirection, int32 RandomSeed, float ReticleSpread)
{
	const FVector EndTrace = Origin + ShootDirection * WeaponConfig.WeaponRange;
	const FVector EndPoint = Impact.GetActor() ? Impact.ImpactPoint : EndTrace;
	DrawDebugLine(GetWorld(), Origin, EndPoint, FColor::Black, true, 10000.f, 0, 1.f);
}

