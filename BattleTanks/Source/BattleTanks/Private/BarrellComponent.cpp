// Fill out your copyright notice in the Description page of Project Settings.
#include "..\Public\BarrellComponent.h"

void UBarrellComponent::Elevate( float RelativeSpeed ) {
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f , 1.f);
	float degreesPerFrame = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float rawElevation = RelativeRotation.Pitch + degreesPerFrame;
	float clampedElevation = FMath::Clamp( rawElevation, minMaxElevation.X, minMaxElevation.Y );

	SetRelativeRotation( FRotator(clampedElevation, 0, 0) );
}
