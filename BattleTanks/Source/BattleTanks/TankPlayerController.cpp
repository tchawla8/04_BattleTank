// Fill out your copyright notice in the Description page of Project Settings.
#include "DrawDebugHelpers.h"
#include "TankPawn.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

ATankPawn* ATankPlayerController::GetControlledTank() const {
	return Cast<ATankPawn>( GetPawn() );
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	if( controlledTank != nullptr ) {
		UE_LOG( LogTemp, Warning, TEXT( "Controlled Tank is -> %s" ), *(controlledTank->GetName()) );
	}
	UE_LOG( LogTemp, Warning, TEXT( "Begin Play called on Tank Player Controller" ) )
}

void ATankPlayerController::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair() {
	auto controller = GetControlledTank();
	if( controller == nullptr ) {
		return;
	}
	FVector HitLocation( 0.0f );
	if( GetSightRayHitLocation( HitLocation ) ) {
		//Aim at the crosshair hit location.
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& hitLocation ) {
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize( viewportSizeX, viewportSizeY );
	FVector2D screenLocation( viewportSizeX * CrosshairLocationX, viewportSizeY * CrosshairLocationY );
	FVector worldLocation, worldDir;
	if( !DeprojectScreenPositionToWorld( screenLocation.X, screenLocation.Y, worldLocation, worldDir ) ) {
		return false;
	}

	FHitResult hitResult;
	//Perform a Line Trace and store the result in FHitResult.
	FVector startLoc = PlayerCameraManager->GetCameraLocation();
	DrawDebugLine(GetWorld(), startLoc, startLoc + worldDir * raycastDistance, FColor::Cyan, false, 10.f, 0, 0.1f);
	if( GetWorld() == nullptr || !GetWorld()->LineTraceSingleByChannel( hitResult,
		worldLocation,
		worldLocation + worldDir * raycastDistance,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams( "", false, GetControlledTank() )
	) ) {
		return false;
	}
	//Use the hitresult to plug in the hitLocation.
	UE_LOG(LogTemp, Warning, TEXT("Line Trace has hit -> %s"), *(hitResult.Actor->GetName()))
	hitLocation = hitResult.Location;
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location -> %s"), *(screenLocation.ToString()))
	return true;
}
