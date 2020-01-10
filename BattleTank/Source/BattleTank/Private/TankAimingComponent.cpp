// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//Delay all aiming components on beginplay
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Ask if it is still reloading
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
		//TODO Aiming and locked state
	}

	else if(IsBarrelMoving()) 
	{
		FiringState = EFiringState::Aiming;
	}

	else
	{
		FiringState = EFiringState::Locked;
	}
	// ...
}

bool UTankAimingComponent::IsBarrelMoving()
{

	if (!ensure(Barrel)) { return false; }
	auto BarrelRotator = Barrel->GetForwardVector();
	return !BarrelRotator.Equals(AimDirection, 1.0f);

}	

void UTankAimingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }
	auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace


	);

	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s, LaunchSpeed: %f"), *OurTankName, *AimDirection.ToString(), LaunchSpeed);
		MoveTAndBTowards(AimDirection);
		float time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f , aim solve found"), time);
		return;


	}
	float time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f , No aim solve found"), time);

}

void UTankAimingComponent::MoveTAndBTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }
	//Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaBRotation = AimAsRotator - BarrelRotator;
	auto DeltaTRotation = AimAsRotator - TurretRotator;


	Turret->Rotate(DeltaTRotation.Yaw);
	Barrel->Elevate(DeltaBRotation.Pitch); //TODO REMOVE MAGIC NUMBER




}

void UTankAimingComponent::Fire()
{

	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	if (FiringState  != EFiringState::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))

			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}