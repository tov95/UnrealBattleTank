// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAiController.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PTargetTank = GetPlayerTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ai CONTROLLER/s NOT POSSESSING TANK"));
		return;


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ai Controller controlling: %s"), *(ControlledTank->GetName()));
		if (!PTargetTank)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Player target tank not found"), *(ControlledTank->GetName()));
			return;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has found %s"), *(ControlledTank->GetName()), *(PTargetTank->GetName()));
		}

	}


	
}

// Called every frame
void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{

		//TODO MOVE TOWARDS THE PLAYER
		//AIM TOWARDS PLAYER
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//FIRE IF READY

	}

	//UE_LOG(LogTemp, Warning, TEXT("PlayerController tick"));


}


ATank* ATankAiController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

