// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"

// Sets default values
ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fSpeed = 0;
	fMaxSpeed = 50;

	fAcceleration = 2;
	fRotationSpeed = 0.1;
	fRotationX = 0;
	fActualMaxSpeed = 0;

	iTorqueLevel = 5;
	iMaxTorqueLevel = 5;
	iMinTorqueLevel = -3;
}

// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();

}

void ASpaceship::ProcessAcceleration(const float& deltaTime)
{
	
	FString TheFloatStr = FString::SanitizeFloat(fMaxSpeed);
	GEngine->AddOnScreenDebugMessage(-1, 0.0, FColor::Red, *TheFloatStr);
	
	if (this->fSpeed == this->fActualMaxSpeed) 
	{
		this->fSpeed = fActualMaxSpeed;
		return;
	}

	if (this->iTorqueLevel > 0)
	{
		this->fSpeed += this->fAcceleration * deltaTime;
		if (this->fSpeed > this->fActualMaxSpeed)
		{
			this->fSpeed = this->fActualMaxSpeed;
			return;
		}
	}

	if (this->iTorqueLevel < 0)
	{
		this->fSpeed -= this->fAcceleration * deltaTime;
		if (this->fSpeed < this->fActualMaxSpeed && this->iTorqueLevel < 0)
		{
			this->fSpeed = this->fActualMaxSpeed;
			return;
		}
	}

	if (this->iTorqueLevel == 0)
	{
		if (this->fSpeed > 0)this->fSpeed -= this->fAcceleration * deltaTime;
		if (this->fSpeed < 0)this->fSpeed += this->fAcceleration * deltaTime;

		if (abs(this->fSpeed) - this->fAcceleration < 0)
		{
			this->fSpeed = 0;
		}
	}
}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceship::setTorqueLevel(const int lvl)
{
	this->iTorqueLevel = lvl;
	if (this->iTorqueLevel > this->iMaxTorqueLevel)this->iTorqueLevel = this->iMaxTorqueLevel;
	else if (this->iTorqueLevel < this->iMinTorqueLevel)this->iTorqueLevel = this->iMinTorqueLevel;
	this->calculateActualMaxSpeed();
}

void ASpaceship::calculateActualMaxSpeed()
{
	if (this->iTorqueLevel > 0)
	{
		this->fActualMaxSpeed = (float)this->iTorqueLevel / (float)this->iMaxTorqueLevel;
		this->fActualMaxSpeed *= this->fMaxSpeed;
	}
	else if (this->iTorqueLevel < 0)
	{
		this->fActualMaxSpeed = (float)this->iTorqueLevel / (float)this->iMinTorqueLevel;
		this->fActualMaxSpeed *= -1 * this->fMaxSpeed;
	}
	else if (this->iTorqueLevel == 0)
	{
		this->fMaxSpeed = 0;
	}
}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

