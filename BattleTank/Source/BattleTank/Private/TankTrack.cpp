// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SpawnPont.h"
#include "SprungWheel.h"


// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();


}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*>ResultArray; //Init Result Array
	TArray<USceneComponent*> Children; //Init OUT Param Children
	GetChildrenComponents(true, Children); //GetChildrenComponent of Tank Track
	for (USceneComponent* Child : Children) //For Each child of Tank track, check if child is a "USpawnPont" if not, move on to the next. then for each SpawnPont, check if its child is "ASprungWheel"
											//If yes, add to result array.
	{
		auto SpawnPointChild= Cast<USpawnPont>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnChild);
		if (!SprungWheel) continue;
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}



UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetNotifyRigidBodyCollision(true);


}




void UTankTrack::SetThrottle(float Throttle)
{

	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	//Drive The Tracks
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{

	auto Name = GetName();
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;

	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (auto Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}