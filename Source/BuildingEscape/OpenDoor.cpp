// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	OriginalYaw = InitialYaw;
	CurrentYaw = InitialYaw;
	OpenAngle =  OpenAngle + InitialYaw;
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no pressureplate set"), *GetOwner()->GetName());
	}

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		if(GetWorld()->GetTimeSeconds()-DoorLastOpened>DoorCloseDelay){
			ShutDoor(DeltaTime);
		}
		
	}

}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), CurrentYaw);
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DoorSpeedOpen * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}

void UOpenDoor::ShutDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OriginalYaw, DoorSpeedClose * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}