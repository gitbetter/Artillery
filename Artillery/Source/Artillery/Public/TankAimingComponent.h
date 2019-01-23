// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AExplosiveShell;

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

	UFUNCTION(BlueprintCallable, Category = Input)
	void Fire();

	void AimAt(FVector AimLocation);

protected:
	UTankAimingComponent();

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState firingState = EFiringState::Reloading;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AExplosiveShell> ProjectileShellBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeInSeconds = 3.0f;

	float lastFireTime = 0.0f;

	FVector aimDirection;

	void MoveBarrel(const FVector& aimDirection);

	bool IsBarrelMoving() const;
};
