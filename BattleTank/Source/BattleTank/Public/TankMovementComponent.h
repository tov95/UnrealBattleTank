// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
class ATank;

/**
 * Responsible for driving the tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = FBWInput)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = FBWInput)
	void IntendRotateRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = FBWInput)
	void IntendRotateLeft(float Throw);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	//TODO Check best protection

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	UStaticMeshComponent* Tank = nullptr;
	


};
