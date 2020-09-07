// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Engine/World.h"

ATankAIController::ATankAIController() {
	playerController = nullptr;
}

void ATankAIController::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
	AimAtTarget();
}

ATankPawn* ATankAIController::GetControlledPawn() const {
	return Cast<ATankPawn>( GetPawn() );
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto controlledAIPawn = GetControlledPawn();
	if( controlledAIPawn != nullptr ) {
		UE_LOG( LogTemp, Warning, TEXT( "Controlled AI Pawn -> %s" ), *(controlledAIPawn->GetHumanReadableName()) );
	}
	playerController = Cast<ATankPlayerController>( GetFirstPlayerController() );
	if( playerController != nullptr ) {
		UE_LOG( LogTemp, Warning, TEXT( "Player Controller found -> %s" ), *(playerController->GetName()) )
	}
}

APlayerController* ATankAIController::GetFirstPlayerController() {
	UWorld* world = GetWorld();
	APlayerController* controller = nullptr;
	if( world == nullptr ) {
		return nullptr;
	}
	FConstPlayerControllerIterator iter = world->GetPlayerControllerIterator();
	while( iter ) {
		controller = iter->Get();
		if( controller == nullptr ) {
			continue;
			++iter;
		}
		break;
		++iter;
	}
	iter.Reset();
	return controller;
}

void ATankAIController::AimAtTarget() const {
	auto controlledPawn = GetControlledPawn();
	if( playerController == nullptr || controlledPawn == nullptr || playerController->GetControlledTank() == nullptr) {
		return;
	}
	//TODO: Find the distance between ai and player or raycast from ai to player.
	controlledPawn->AimAt(playerController->GetControlledTank()->GetActorLocation());
}