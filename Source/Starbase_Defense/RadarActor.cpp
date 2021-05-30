// Fill out your copyright notice in the Description page of Project Settings.


#include "RadarActor.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ARadarActor::ARadarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARadarActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARadarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AActor*> ARadarActor::SpotEnemies()
{
	TArray<AActor*> FoundActors, ActorsInRange;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, FoundActors);
	float distanceToEnemy;
	for (int i = 0; i < FoundActors.Num(); i++) {
		{
			distanceToEnemy = FVector::Dist(FVector(FoundActors[i]->GetActorLocation().X, FoundActors[i]->GetActorLocation().Y, 0), FVector(this->GetActorLocation().X, this->GetActorLocation().Y, 0));
			if (distanceToEnemy <= signalRange)
				ActorsInRange.Add(FoundActors[i]);
		}
	}
	//komentarz
	return ActorsInRange;
}

