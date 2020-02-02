// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->SetupAttachment(Spring);

	AxelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxelConstraint"));
	AxelConstraint->SetupAttachment(Axel);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axel);







}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(GetAttachParentActor())) { return; }
	auto TankRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	auto AxelPrim = Cast<UPrimitiveComponent>(Axel);
	Spring->SetConstrainedComponents(TankRoot, NAME_None, AxelPrim, NAME_None);

	auto WheelPrim = Cast<UPrimitiveComponent>(Wheel);
	AxelConstraint ->SetConstrainedComponents(AxelPrim, NAME_None, WheelPrim, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

