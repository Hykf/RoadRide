// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Engine/World.h"
#include "Road.generated.h"

UCLASS()
class ROADRIDE_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoad();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USplineComponent* RoadSpline;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ActorClassToSpawn;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
