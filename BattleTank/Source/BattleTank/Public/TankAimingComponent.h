// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //Forward Declaration
class UTankTurret;
class AProjectile;

//Enum Class for states
UENUM()

enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

//Hold barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FVector AimDirection;


	void AimAt(FVector HitLocation);
	void MoveTAndBTowards(FVector AimDirection);

	bool IsBarrelMoving();
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();



	float ReloadTimeInSeconds = 3.0f;
	float AmmoLoadTimeInSeconds = 6.0f;
	double LastFireTime = 0;
	double LastAmmoTime = 0;

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int GetRoundsLeft() const;

	int RoundsLeft = 3;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;


	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

		
};
