// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation, float launchSpeed)
{
	if (!Barrel) return;

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
	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate(5);
}

