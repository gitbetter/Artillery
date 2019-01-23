// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveShell.h"
#include "ShellMovementComponent.h"

// Sets default values
AExplosiveShell::AExplosiveShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShellMovementComponent = CreateDefaultSubobject<UShellMovementComponent>(FName("Shell Movement"));
	ShellMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AExplosiveShell::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveShell::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AExplosiveShell::LaunchProjectile(float speed) {
	ShellMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ShellMovementComponent->Activate();
}

