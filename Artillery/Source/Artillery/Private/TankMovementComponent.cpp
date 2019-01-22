// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack * LeftTankTrack, UTankTrack * RightTankTrack) {
	LeftTrack = LeftTankTrack;
	RightTrack = RightTankTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector AIForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float intendedRightThrow = FVector::CrossProduct(AIForwardVector, AIForwardIntention).Z;
	IntendTurnRight(intendedRightThrow);

	float intendedForwardThrow = FVector::DotProduct(AIForwardVector, AIForwardIntention);
	IntendMoveForward(intendedForwardThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
