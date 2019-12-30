// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//move out the turret right amount this frame

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDPS * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	//UE_LOG(LogTemp, Warning, TEXT("Turret Yaw: %f"), Rotation);
	SetRelativeRotation(FRotator(0, Rotation, 0));

	//given max elevation speed and the frame time
}