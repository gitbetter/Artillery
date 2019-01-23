// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* aimingComp = GetAimingComponent();
	if (ensure(aimingComp)) {
		FoundAimingComponent(aimingComp);
	}
}

UTankAimingComponent* ATankPlayerController::GetAimingComponent() const {
	return GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!ensure(GetAimingComponent())) return;

	FVector HitLocation = FVector::ZeroVector;
	if (GetSightRayHitLocation(HitLocation)) {
		GetAimingComponent()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & outHitLocation) const {
	// find the crosshair position in pixel coordinates
	FVector2D screenLocation;
	GetCrosshairScreenLocation(screenLocation);

	// Deproject the 2D crosshair screen pixel coordinates to 3D world space position
	FVector cameraLookPosition, cameraLookDirection;
	if (!DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraLookPosition, cameraLookDirection)) return false;

	FHitResult hitLocation;
	if (!GetLookVectorHitLocation(hitLocation, cameraLookDirection)) return false;

	outHitLocation = hitLocation.ImpactPoint;

	return true;
}

void ATankPlayerController::GetCrosshairScreenLocation(FVector2D& screenLocation) const {
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);
}

bool ATankPlayerController::GetLookVectorHitLocation(FHitResult& outHitLocation, FVector& lookDirection) const {
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + lookDirection * lineTraceRange;
	return GetWorld()->LineTraceSingleByChannel(outHitLocation, startLocation, endLocation, ECollisionChannel::ECC_Visibility);
}