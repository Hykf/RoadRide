// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "Road.h"
#include "Engine/World.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxCollisionComponent->SetBoxExtent(FVector(150.0f, 50.0f, 50.0f)); 
	SetRootComponent(BoxCollisionComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Component"));
	StaticMeshComponent->AttachToComponent(BoxCollisionComponent,FAttachmentTransformRules::KeepRelativeTransform);
	DesiredSpeed = FMath::RandRange(500.0f,1250.0f);
	DeltaSpeed =  FMath::RandRange(1.5f,3.0f);;
}



// Called every frame
void ACar::Tick(float DeltaTime)
{
	if(RoadActor)
	{

		DistanceOnRoad += CurrentSpeed * DeltaTime;
		FTransform OnRoadTransform = RoadActor->RoadSpline->GetTransformAtDistanceAlongSpline(DistanceOnRoad,ESplineCoordinateSpace::World);
		FTransform RelTransform;
		RelTransform.SetLocation(OnRoadTransform.GetLocation()+ FVector(0,0,50));
		RelTransform.SetRotation(OnRoadTransform.GetRotation());
		RelTransform.SetScale3D(GetActorScale3D());
		SetActorRelativeTransform(RelTransform);

		UWorld* World = GetWorld();
		
		if(World)
		{
			FVector StartLocation = GetActorLocation() + FVector(140,0,0);
			FVector EndLocation = StartLocation + this->GetActorForwardVector() * CurrentSpeed * 2;
			
			FHitResult HitResult;
			
			FCollisionObjectQueryParams ObjectParams;
			ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
			ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);

			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this);
			
			bool bHit = World->LineTraceSingleByObjectType(HitResult,StartLocation,EndLocation,ObjectParams,CollisionParams);

			if(bHit)
			{
					float DeltaV = 0 - CurrentSpeed;
					DeltaV = DeltaV/0.2f;
					DeltaV = DeltaV * DeltaTime;
					CurrentSpeed += DeltaV;
					CurrentSpeed = FMath::Clamp(CurrentSpeed,0,DesiredSpeed);
					
				}else
				{
					if(CurrentSpeed<DesiredSpeed)
					{
						float DeltaV = (DesiredSpeed / DeltaSpeed) * DeltaTime;
						CurrentSpeed += DeltaV;
						CurrentSpeed = FMath::Clamp(CurrentSpeed,0,DesiredSpeed);
						
					}
				}
			
				if(DistanceOnRoad>=RoadActor->RoadSpline->GetSplineLength())
				{
					this->Destroy();
				}
			
		}
	}
}



