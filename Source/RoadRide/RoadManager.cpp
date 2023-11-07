// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadManager.h"

// Sets default values
ARoadManager::ARoadManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARoadManager::BeginPlay()
{
	Super::BeginPlay();
	
			//SpawnCar();
}

void ARoadManager::StartRandomTimer()
{
	float RandomDelay = FMath::FRandRange(2.5f, 5.0f);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARoadManager::SpawnCar, RandomDelay, false);
}

void ARoadManager::SpawnCar()
{
	
	if ( GetWorld() && SpawnedRoad)
	{
		FVector Loc = SpawnedRoad->RoadSpline->GetLocationAtSplinePoint(0,ESplineCoordinateSpace::Local) + FVector(0,0,100);
		FRotator Rot = GetActorRotation();
		FVector Scale = FVector(1.0f,1.0f,1.0f);
		
		FTransform SpawnTransform = FTransform(Rot,Loc,Scale);
	
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		ACar* SpawnedCar = GetWorld()->SpawnActor<ACar>(CarBlueprint, SpawnTransform, SpawnParams);
		
		if(SpawnedCar)
		{
			SpawnedCar->RoadActor = SpawnedRoad;
		}
		
	}
	StartRandomTimer();
}
