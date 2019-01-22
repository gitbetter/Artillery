// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UENUM()
enum class EFiringState: uint8 {
	Locked, Aiming, Reloading
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARTILLERY_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector AimLocation, float launchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState firingState = EFiringState::Aiming;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrel(const FVector& aimDirection);
};
