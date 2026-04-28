// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Count = 0;
	EventCount = 0;
	MoveDistance = 0.f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(0.0f, 0.0f, 50.0f));
	for(Count = 0; Count < 10; ++Count)
	{
		if(TriggerEvent())
		{
			EventCount++;
			Move();
			Turn();
		}
	}

	FString LogString = FString::Printf(TEXT("Total Move Distance: %f\nTotal EventCount: %d"), MoveDistance, EventCount);
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, LogString);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *LogString);
}

void AMyActor::Move()
{
	FVector Target;
	Target.X = FMath::RandRange(-100.0f, 100.0f);
	Target.Y = FMath::RandRange(-100.0f, 100.0f);
	Target.Z = 0.0f;
	FVector CurrentLocation = GetActorLocation();
	FVector Destination = CurrentLocation + Target;
	MoveDistance += FVector::Dist(CurrentLocation, Destination);
	AddActorWorldOffset(Target);
	FString LogString = FString::Printf(TEXT("Current %d Location: %s"), Count, *Destination.ToString());
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, LogString);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *LogString);
}

void AMyActor::Turn()
{
	FRotator DeltaRotation;
	DeltaRotation.Yaw = FMath::RandRange(-10.0f, 10.0f);
	DeltaRotation.Pitch = FMath::RandRange(-10.0f, 10.0f);
	DeltaRotation.Roll = FMath::RandRange(-10.0f, 10.0f);
	AddActorWorldRotation(DeltaRotation);

	FRotator CurrentRotation = GetActorRotation();
	FString LogString = FString::Printf(TEXT("Current %d Rotation: %s"), Count, *CurrentRotation.ToString());
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, LogString);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *LogString);
}

bool AMyActor::TriggerEvent()
{
	return FMath::RandRange(0, 1) == 1;
	//return FMath::RandBool();
}