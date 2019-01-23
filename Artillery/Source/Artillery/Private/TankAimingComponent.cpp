// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "ExplosiveShell.h"
#include "Components/StaticMeshComponent.h"

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel)) return;

	FVector outLaunchVelocity(0);
	FVector startLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	if (!UGameplayStatics::SuggestProjectileVelocity(
			this, 
			outLaunchVelocity, 
			startLocation, 
			AimLocation, 
			launchSpeed, 
			false, 
			0, 
			0, 
			ESuggestProjVelocityTraceOption::DoNotTrace)
		) return;

	FVector aimDirection = outLaunchVelocity.GetSafeNormal();
	FString tankName = GetOwner()->GetName();
	
	MoveBarrel(aimDirection);
}

void UTankAimingComponent::MoveBarrel(const FVector& aimDirection)
{
	if (!ensure(Barrel && Turret)) return;

	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->Rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel && ProjectileShellBlueprint)) return;

	bool isReloaded = (GetWorld()->GetTimeSeconds() - lastFireTime) > reloadTimeInSeconds;

	if (isReloaded) {
		AExplosiveShell* shell = GetWorld()->SpawnActor<AExplosiveShell>(
			ProjectileShellBlueprint,
			Barrel->GetSocketLocation("ProjectileStart"),
			Barrel->GetSocketRotation("ProjectileStart")
		);

		shell->LaunchProjectile(launchSpeed);
		lastFireTime = GetWorld()->GetTimeSeconds();
	}
}

