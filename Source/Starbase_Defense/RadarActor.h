// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RadarActor.generated.h"

UCLASS()
class STARBASE_DEFENSE_API ARadarActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARadarActor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float signalRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<AActor> EnemyClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MyOwn")
		TArray<AActor*> SpotEnemies();

};
