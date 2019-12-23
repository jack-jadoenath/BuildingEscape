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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw =  TargetYaw + InitialYaw  ;
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), CurrentYaw);

	// FMath::Lerp(/* StartingYaw, TargetYaw, Percentage 0-1.0f*/);
	//float StartingYaw = GetOwner()->GetActorRotation().Yaw;
	//YawTo.Yaw = FMath::Lerp(IntitialYaw, YawTo.Yaw, 0.05f);
	// FRotator YawStart = FRotator(0.0f, InitialYaw, 0.0f);
	// FRotator YawTo = FRotator(0.0f, TargetYaw, 0.0f);
	// YawTo.Yaw = FMath::Lerp(YawStart.Yaw, YawTo.Yaw, 0.001f);

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, 1.0f * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}

