// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAiController.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto* GetPlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto* GetControlledTank = Cast<ATank>(GetPawn());


	if (!GetPlayerTank) { return; }
	if (!GetControlledTank) { return; }
	if (GetPlayerTank)
	{

		//TODO MOVE TOWARDS THE PLAYER
		//AIM TOWARDS PLAYER
		GetControlledTank->AimAt(GetPlayerTank->GetActorLocation());
		GetControlledTank->Fire();

	}

	//UE_LOG(LogTemp, Warning, TEXT("PlayerController tick"));


}


