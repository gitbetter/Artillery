// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float throttle) {
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

UPrimitiveComponent * UTankTrack::GetTankRoot() {
	return Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce() {
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	FVector RequiredAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();

	FVector SidewaysFriction = RequiredAcceleration * GetTankRoot()->GetMass() / 2;
	GetTankRoot()->AddForce(SidewaysFriction);
}

void UTankTrack::DriveTrack() {
	FVector appliedForce = GetForwardVector() * currentThrottle * MaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	GetTankRoot()->AddForceAtLocation(appliedForce, forceLocation);
}