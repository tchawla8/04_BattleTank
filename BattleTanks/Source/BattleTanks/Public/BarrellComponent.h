// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BarrellComponent.generated.h"

/**
 *
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UBarrellComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY( EditAnywhere, Category = Setup )
		float MaxDegreesPerSecond = 20.f;
	UPROPERTY( EditAnywhere, Category = Setup )
		FVector2D minMaxElevation = {0.f, 20.f};
	UPROPERTY( EditAnywhere, Category = Setup )
		bool preventSelfCollision;

public:
	//Relative speed can take values +1 and -1
	void Elevate( float RelativeSpeed );

};
