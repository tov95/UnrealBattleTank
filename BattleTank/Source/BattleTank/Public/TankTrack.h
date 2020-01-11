// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  Tank Tack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);

    //Max  Force per track in newtons
    UPROPERTY(EditDefaultsOnly, Category = Setup)
        float TrackMaxDrivingForce = 20000000;

private:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& hit);
    UTankTrack();
    void ApplySidewaysForce();
    void DriveTrack();
    float CurrentThrottle = 0;
    // Assume 40 tonne tank acceleration at 1g
};
