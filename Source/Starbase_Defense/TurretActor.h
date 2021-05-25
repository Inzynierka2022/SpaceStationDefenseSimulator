// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/Components/ArrowComponent.h>
#include "TurretActor.generated.h"

UCLASS()
class STARBASE_DEFENSE_API ATurretActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretActor();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<AActor> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<AActor> BulletClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticBottom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* RotatableTop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent* BulletArrow;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "Variables")
		float closestEnemy = 10000;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MyOwn")
		AActor* findClosestEnemy();

	UFUNCTION(BlueprintCallable, Category = "MyOwn")
		void RotateToDefault (float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "MyOwn")
		void RotateTowards(FVector TargetLocation, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "MyOwn")
		bool CheckIfAimingAtEnemy();

	UFUNCTION(BlueprintCallable, Category = "MyOwn")
		void fire();
};
