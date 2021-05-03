// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"

UCLASS()
class STARBASE_DEFENSE_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Movement")
	void ProcessAcceleration(const float &deltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void setTorqueLevel(const int lvl);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void calculateActualMaxSpeed();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
		float fSpeed;
	UPROPERTY(BlueprintReadWrite)
		float fMaxSpeed;

	UPROPERTY(BlueprintReadWrite)
		float fAcceleration;
	UPROPERTY(BlueprintReadWrite)
		float fRotationSpeed;
	UPROPERTY(BlueprintReadWrite)
		float fRotationX;
	UPROPERTY(BlueprintReadWrite)
		float fActualMaxSpeed;
	UPROPERTY(BlueprintReadWrite)
		int iTorqueLevel;
	UPROPERTY(BlueprintReadWrite)
		int iMaxTorqueLevel;
	UPROPERTY(BlueprintReadWrite)
		int iMinTorqueLevel;

	UPROPERTY(BlueprintReadWrite)
		bool bRotated;
	UPROPERTY(BlueprintReadWrite)
		FVector v;
};
