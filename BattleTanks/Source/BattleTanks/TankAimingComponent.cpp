// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Public/BarrellComponent.h"
#include "TankPawn.h"
#include "Engine\World.h"
#include "Kismet\GameplayStatics.h"
#include "Components\StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();

	// ...

}

void UTankAimingComponent::AimAt( FVector hitLocation, float launchSpeed ) {
	if( GetOwner() == nullptr ) {
		return;
	}
	//Call the BarrellComponent SuggestLaunchVelocity.
	//barrellComponent->AimAt
	if( barrellComponent == nullptr || GetWorld() == nullptr ) {
		return;
	}
	FVector launchVelocity( 0.f, 0.f, 0.f );
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		launchVelocity,
		barrellComponent->GetComponentLocation(),
		hitLocation,
		launchSpeed,
		false,
		0.f,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		{},
		true
	);

	if( bHaveAimSolution ) {
		FVector launchDirection = launchVelocity.GetSafeNormal();
		MoveBarrellTowards( barrellComponent, launchDirection);
		UE_LOG( LogTemp, Warning, TEXT( "%s Launch Velocity-> %s | Launch Direction -> %s" ), *(GetOwner()->GetName()), *launchVelocity.ToString(), *launchDirection.ToString() )
	}
	else {
		UE_LOG( LogTemp, Warning, TEXT( "Aim Solution not found" ))
	}
}

void UTankAimingComponent::MoveBarrellTowards(UBarrellComponent* barrellComponent, FVector aimDirection ) {
	auto barrellRotator = barrellComponent->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	//Calculate delta Rotation between aimDirection and barrellRotator.
	auto deltaRotator = aimRotator - barrellRotator;
	//
	barrellComponent->Elevate( deltaRotator.Pitch );
}

void UTankAimingComponent::SetBarrellComponent( UBarrellComponent* component ) {
	barrellComponent = component;
}