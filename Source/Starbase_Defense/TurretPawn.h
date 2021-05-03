// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ArrowComponent.h"
#include "TurretPawn.generated.h"

UCLASS()
class STARBASE_DEFENSE_API ATurretPawn : public APawn
{
	GENERATED_BODY()

private:
	float closestEnemy = 10000;
	FTimerHandle TimerHandle;
	bool shooting = false;
public:
	// Sets default values for this pawn's properties
	ATurretPawn();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Classes")
		TSubclassOf<AActor> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<AActor> BulletClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent* RotationArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BodyCylinder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* GunCone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent* BulletArrow;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	AActor* findClosestEnemy();
	UFUNCTION(BlueprintCallable, Category = "MyOwn")
		void RotateTowards(FVector TargetLocation, float DeltaTime);
	void CheckIfAimingAtEnemy();
	void fire();
};