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

protected:
	//How Close can the Ai get to you
	UPROPERTY(EditAnywhere, Category = "Setup")
		float AcceptanceRadius = 8000.0f;


private:
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPossessedTankDeath();


	
};
