// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//move out the barrel right amount this frame

	auto ElevationChange = RelativeSpeed * MaxDPS * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevate, MaxElevate);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

//given max elevation speed and the frame time
}