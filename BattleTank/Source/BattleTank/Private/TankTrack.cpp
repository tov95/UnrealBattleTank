// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);


}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& hit)
{
	//Drive The Tracks
	DriveTrack();
	//Apply Sideways Force
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetNotifyRigidBodyCollision(true);


}



void UTankTrack::ApplySidewaysForce()
{
	auto TankName = GetOwner()->GetName();
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto ComponentVelocity = GetComponentVelocity();
	auto RightVector = GetRightVector();
	auto SlippageSpeed(FVector::DotProduct(RightVector, ComponentVelocity));
	//UE_LOG(LogTemp, Warning, TEXT("%s: Slippage speed is %f"), *TankName, SlippageSpeed);

	//workout the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculate and apply sideways force (F=ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two Tracks
	TankRoot->AddForce(CorrectionForce);
}
void UTankTrack::SetThrottle(float Throttle)
{

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{

	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}