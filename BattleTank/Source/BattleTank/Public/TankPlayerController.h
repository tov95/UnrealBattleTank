// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



//Forward Declarations
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:


	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);


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

