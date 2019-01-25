// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "ExplosiveShell.h"
#include "Components/StaticMeshComponent.h"

UTankAimingComponent::UTankAimingComponent() {
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
	lastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	if ((GetWorld()->GetTimeSeconds() - lastFireTime) < reloadTimeInSeconds) {
		firingState = EFiringState::Reloading;
	} else if (IsBarrelMoving()) {
		firingState = EFiringState::Aiming;
	} else {
		firingState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return firingState;
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

	aimDirection = outLaunchVelocity.GetSafeNormal();
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
	Turret->Rotate(deltaRotator.Yaw >= 180.0 ? -deltaRotator.Yaw : deltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving() const {
	if (!ensure(Barrel)) return false;
	return !Barrel->GetForwardVector().Equals(aimDirection);
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel && ProjectileShellBlueprint)) return;

	if (firingState != EFiringState::Reloading) {
		AExplosiveShell* shell = GetWorld()->SpawnActor<AExplosiveShell>(
			ProjectileShellBlueprint,
			Barrel->GetSocketLocation("ProjectileStart"),
			Barrel->GetSocketRotation("ProjectileStart")
		);

		shell->LaunchProjectile(launchSpeed);
		lastFireTime = GetWorld()->GetTimeSeconds();
	}
}

