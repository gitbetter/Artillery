// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* tank = GetControlledTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Found: %s"), *tank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Not Found"));
	}
}
