// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "Car.h"
#include "Components/SplineMeshComponent.h"


// Sets default values
ARoad::ARoad()
{
	PrimaryActorTick.bCanEverTick = true;
	RoadSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RoadSplineComp"));
	RootComponent = RoadSpline;
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

void ARoad::OnConstruction(const FTransform& Transform)
{
	FVector StartLocation,StartTangent,EndLocation,EndTangent;
	
	for(int i = 0; i< RoadSpline->GetNumberOfSplinePoints() - 1 ; i++)
	{
		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this,USplineMeshComponent::StaticClass());
		
		UStaticMesh* Mesh = RoadMesh;
		UMaterialInterface* Material = RoadMaterial;
		
		SplineMeshComponent->SetStaticMesh(Mesh);
		SplineMeshComponent->SetMaterial(0, Material); 
		SplineMeshComponent->SetRelativeScale3D(FVector(1.0f, 2.0f, 1.0f));
		
		RoadSpline->GetLocationAndTangentAtSplinePoint(i,StartLocation,StartTangent,ESplineCoordinateSpace::Local);
		RoadSpline->GetLocationAndTangentAtSplinePoint(i+1,EndLocation,EndTangent,ESplineCoordinateSpace::Local);
		SplineMeshComponent->SetStartAndEnd(StartLocation,StartTangent,EndLocation,EndTangent);
		
		SplineMeshComponent->RegisterComponentWithWorld(GetWorld());
		SplineMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	}
}

