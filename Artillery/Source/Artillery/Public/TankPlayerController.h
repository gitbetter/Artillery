// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class ARTILLERY_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
private:
	UPROPERTY(EditAnywhere) float crosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere) float crosshairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere) float lineTraceRange = 100000.0f;

	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& outHitLocation) const;
	void GetCrosshairScreenLocation(FVector2D& screenLocation) const;
	bool GetLookVectorHitLocation(FHitResult& outHitLocation, FVector& lookDirection) const;
};
