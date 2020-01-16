// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController tick"));


}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCont NOT POSSESSING TANK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller controlling: %s"), *(ControlledTank->GetName()));
	}

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Contr. Aiming Comp not found"));
	}


}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)){return; }

	FVector OUTHitLocation; // OUT PARAMETER
	bool BGotHitLocation = GetSightRayHitLocation(OUTHitLocation);

	if (BGotHitLocation) //Going to line trace
	{
		AimingComponent->AimAt(OUTHitLocation);
		//Tell turret to aim at the spot
	}


}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;


	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation(ViewportSizeX*CrossHairXLocation, ViewportSizeY* CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *ScreenLocation.ToString())


	//De-project screen position to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	if (OutHitLocation != FVector(0)) {
		return true;
	}
	else
	{
		return false;
	}
}
	//LineTrace along that look direction and see what we hit(up to max range)


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;//ToBeDiscarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);


}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OUTHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		OUTHitLocation = HitResult.Location;
		return true;
	}
	OUTHitLocation = FVector(0);
		return false;

}
