// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Road.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Car.generated.h"

UCLASS(Blueprintable)
class ROADRIDE_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxCollisionComponent;
	UPROPERTY()
	ARoad* RoadActor;
	
	UPROPERTY()
	float CurrentSpeed;
	UPROPERTY()
	float DesiredSpeed;
	UPROPERTY()
	float DistanceOnRoad;
	UPROPERTY()
	float DeltaSpeed;
	
	virtual void Tick(float DeltaTime) override;

};
