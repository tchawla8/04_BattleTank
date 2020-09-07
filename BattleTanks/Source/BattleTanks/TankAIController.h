// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPawn.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankPlayerController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
    ATankPawn* GetControlledPawn() const;
    void BeginPlay() override;
    ATankAIController();
    void Tick(float DeltaTime) override;
private:
    ATankPlayerController* playerController;
    APlayerController* GetFirstPlayerController();
    void AimAtTarget() const;
};
