// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// FRotator Rotation = FRotator(0.0f, 90.0f, 0.0f);
	// GetOwner()->SetActorRotation(Rotation);

	TargetYaw = 90.0f;
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	// FMath::Lerp(/* StartingYaw, TargetYaw, Percentage 0-1.0f*/);

	float StartingYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator YawTo = FRotator(0.0f, TargetYaw, 0.0f);
	YawTo.Yaw = FMath::Lerp(StartingYaw, YawTo.Yaw, 0.05f);

	GetOwner()->SetActorRotation(YawTo);

}

