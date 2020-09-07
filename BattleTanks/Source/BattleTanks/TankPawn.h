// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UBarrellComponent;
class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankPawn : public APawn
{
	GENERATED_BODY()
private:
	UTankAimingComponent* tankAimingComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 100000; // 1000 m/s

public:
	// Sets default values for this pawn's properties
	ATankPawn();
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	void AimAt( FVector HitLocation );
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrellMesh(UBarrellComponent* component);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
