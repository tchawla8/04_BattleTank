// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

/**
 *
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController {
	GENERATED_BODY()
public:
	ATankPawn* GetControlledTank() const;
	void BeginPlay() override;
	void Tick( float DeltaTime ) override;
protected:
	UPROPERTY( EditAnywhere )
		float CrosshairLocationX = 0.5f;
	UPROPERTY( EditAnywhere )
		float CrosshairLocationY = 0.33f;
	UPROPERTY( EditAnywhere )
		float raycastDistance = 10.0f;
private:
	void AimAtCrosshair();
	bool GetSightRayHitLocation( FVector& );
};
