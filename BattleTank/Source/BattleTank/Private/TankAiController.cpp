// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Tank.h" //so we can implement OnDeath

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAiController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnPossessedTankDeath);
		//subscribe to tank death event
	}
}

// Called every frame
void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto* GetPlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto* GetControlledTank = GetPawn();

	if (!ensure(AimingComponent)) { return; }
	if (!ensure(GetPlayerTank)) { return; }
	if (!ensure(GetControlledTank)) { return; }
	if (GetPlayerTank)
	{

		//TODO MOVE TOWARDS THE PLAYER
		MoveToActor(GetPlayerTank, AcceptanceRadius);

		//AIM TOWARDS PLAYER
		AimingComponent->AimAt(GetPlayerTank->GetActorLocation());

		//If aim or locked
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}


	}

	//UE_LOG(LogTemp, Warning, TEXT("PlayerController tick"));


}

void ATankAiController::OnPossessedTankDeath()
{

	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();

	

}


