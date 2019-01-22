// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "ExplosiveShell.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay( ) {
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation) {
	if (!TankAimingComponent) return; 
	TankAimingComponent->AimAt(HitLocation, launchSpeed);
}

void ATank::Fire() {
	bool isReloaded = (GetWorld()->GetTimeSeconds() - lastFireTime) > reloadTimeInSeconds;

	if (Barrel && isReloaded) {
		AExplosiveShell* shell = GetWorld()->SpawnActor<AExplosiveShell>(
			ProjectileShellBlueprint,
			Barrel->GetSocketLocation("ProjectileStart"),
			Barrel->GetSocketRotation("ProjectileStart")
			);

		shell->LaunchProjectile(launchSpeed);
		lastFireTime = GetWorld()->GetTimeSeconds();
	}
}

