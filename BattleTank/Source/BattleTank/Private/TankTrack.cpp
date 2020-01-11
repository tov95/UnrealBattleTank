// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Calculate the slippage speed
	auto TankName = GetOwner()->GetName();
	auto ComponentVelocity = GetComponentVelocity();
	auto RightVector = GetRightVector();
	auto SlippageSpeed(FVector::DotProduct(ComponentVelocity, RightVector));
	UE_LOG(LogTemp, Warning, TEXT("%s: Slippage speed is %f"), *TankName, SlippageSpeed);

	//workout the required acceleration this frame to correct
	//Calculate and apply sideways force (F=ma)


}
void UTankTrack::SetThrottle(float Throttle)
{

	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * FMath::Clamp<float>(Throttle, -0.5f, 0.5f) * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}