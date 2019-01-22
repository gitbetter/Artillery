// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* playerTank = Cast<ATank>(playerPawn);
	ATank* controlledTank = Cast<ATank>(GetPawn());

	if (playerTank) {
		// Move towards player
		MoveToActor(playerTank, acceptanceRadius);

		// Aim towards player
		controlledTank->AimAt(playerTank->GetActorLocation());

		// Fire if ready
		controlledTank->Fire();
	}
}
