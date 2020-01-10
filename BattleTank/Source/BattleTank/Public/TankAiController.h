// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "TankAiController.generated.h"


//Forward Declaration
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()


public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	//How Close can the Ai get to you
	float AcceptanceRadius = 0.0f;


	
};
