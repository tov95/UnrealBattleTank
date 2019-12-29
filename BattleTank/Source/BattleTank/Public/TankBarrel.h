// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category =Setup)
		float MaxDPS = 5; //TODO sensible default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevate = 40; //TODO sensible default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevate = 0; //TODO sensible default
	
};
