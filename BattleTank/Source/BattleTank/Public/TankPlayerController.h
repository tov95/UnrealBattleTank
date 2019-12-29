// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



//Forward Declarations
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;



private:
	//Start the tank moving the barrel so that the shot
	//will hit the target
	void AimTowardsCrosshair();
	//Return an Out Parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333f;

	FVector2D ScreenLocation;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	bool GetLookVectorHitLocation(FVector& OUTHitLocation, FVector LookDirection) const;



};

