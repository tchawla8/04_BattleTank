// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UBarrellComponent;  //Forward Declare

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UBarrellComponent* barrellComponent = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void MoveBarrellTowards(UBarrellComponent *component, FVector);

public:
	UTankAimingComponent();
	// Called every frame
	void AimAt( FVector, float );
	void SetBarrellComponent(UBarrellComponent* component);
};
