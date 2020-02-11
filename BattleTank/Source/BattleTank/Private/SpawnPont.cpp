// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPont.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
USpawnPont::USpawnPont()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void USpawnPont::BeginPlay()
{
	Super::BeginPlay();
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!SpawnedActor) { return; }
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());

	// ...
	
}


// Called every frame
void USpawnPont::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

