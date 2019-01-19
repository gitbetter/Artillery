// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* tank = GetControlledTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("NPC Tank Found: %s"), *tank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("NPC Tank Not Found"));
	}
}
