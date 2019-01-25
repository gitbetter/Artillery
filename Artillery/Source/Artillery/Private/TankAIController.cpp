// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* controlledTank = GetPawn();

	if (!ensure(playerPawn && controlledTank)) return;

	// Move towards player
	MoveToActor(playerPawn, acceptanceRadius);

	// Aim towards player
	UTankAimingComponent* aimingComp = GetAimingComponent();
	if (ensure(aimingComp)) {
		GetAimingComponent()->AimAt(playerPawn->GetActorLocation());
	}

	if (GetAimingComponent()->GetFiringState() == EFiringState::Locked) {
		GetAimingComponent()->Fire();
	}
}

UTankAimingComponent* ATankAIController::GetAimingComponent() const {
	return GetPawn()->FindComponentByClass<UTankAimingComponent>();
}
