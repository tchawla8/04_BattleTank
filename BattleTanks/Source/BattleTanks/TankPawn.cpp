// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankPawn.h"


// Sets default values
ATankPawn::ATankPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Create a Aiming Component using CreateDefaultSubobject.
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>( FName( "AimingComponent" ) );
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay() {
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) {
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ATankPawn::AimAt( FVector HitLocation ) {
	if( tankAimingComponent == nullptr ) {
		return;
	}
	tankAimingComponent->AimAt( HitLocation , launchSpeed);
}

void ATankPawn::SetBarrellMesh( UBarrellComponent *component ) {
	if( component == nullptr || tankAimingComponent == nullptr) {
		return;
	}
	tankAimingComponent->SetBarrellComponent(component);
}
