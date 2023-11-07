// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.h"
#include "Road.h"
#include "RoadManager.generated.h"

UCLASS()
class ROADRIDE_API ARoadManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadManager();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ACar> CarBlueprint;

	UPROPERTY()
	ARoad* SpawnedRoad;

	UPROPERTY()
	FTimerHandle TimerHandle;
	

	UFUNCTION()
	void StartRandomTimer();
	UFUNCTION()
	void SpawnCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
