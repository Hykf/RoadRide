// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "RoadManager.h"


// Sets default values
ARoad::ARoad()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARoad::BeginPlay()
{
	Super::BeginPlay();

	SpawnCar();
}

void ARoad::SpawnCar()
{
	if ( GetWorld())
	{
		FVector Loc = this->RoadSpline->GetLocationAtSplinePoint(0,ESplineCoordinateSpace::Local) + FVector(0,0,100);
		FRotator Rot = GetActorRotation();
		FVector Scale = FVector(1.0f,1.0f,1.0f);
		
		FTransform SpawnTransform = FTransform(Rot,Loc,Scale);
	
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		ACar* SpawnedCar = GetWorld()->SpawnActor<ACar>(CarBlueprint, SpawnTransform, SpawnParams);
		
		if(SpawnedCar)
		{
			SpawnedCar->RoadActor = this;
		}
	}
	StartRandomTimer();
}

void ARoad::StartRandomTimer()
{
	float RandomDelay = FMath::FRandRange(2.5f, 5.0f);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARoad::SpawnCar, RandomDelay, false);
}

