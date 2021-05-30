// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretActor.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ATurretActor::ATurretActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 5;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	StaticBottom = CreateDefaultSubobject<UStaticMeshComponent>(L"Body");
	StaticBottom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticBottom->RegisterComponent();

	RotatableTop = CreateDefaultSubobject<UStaticMeshComponent>(L"Gun");
	RotatableTop->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	RotatableTop->RegisterComponent();
	BulletArrow = CreateDefaultSubobject<UArrowComponent>(L"BulletArrow");
	BulletArrow->AttachToComponent(RotatableTop, FAttachmentTransformRules::KeepRelativeTransform);
	BulletArrow->RegisterComponent();
}

// Called when the game starts or when spawned
void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* ATurretActor::findClosestEnemy()
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, FoundActors);
	if (FoundActors.Num() == 0)
	{
		closestEnemy = 10000;
		return nullptr;
	}
	int closestIndex;
	float closestValue = 10000;
	int tempValue;
	for (int i = 0; i < FoundActors.Num(); i++) {
		tempValue = FVector::Dist(FoundActors[i]->GetActorLocation(), this->GetActorLocation());
		if (closestValue > tempValue)
		{
			closestIndex = i;
			closestValue = tempValue;
		}
	}
	closestEnemy = closestValue;
	return FoundActors[closestIndex];
}

void ATurretActor::RotateToDefault(float DeltaTime)
{
	FRotator NewRot = FMath::RInterpConstantTo(this->RotatableTop->GetRelativeRotation(), FRotator(0,0,0), DeltaTime, RotationSpeed);
	RotatableTop->SetRelativeRotation(NewRot);
}

void ATurretActor::RotateTowards(FVector TargetLocation, float DeltaTime)
{
	FRotator TurretRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), FVector(TargetLocation.X, TargetLocation.Y, this->GetActorLocation().Z));
	FRotator NewRot = FMath::RInterpConstantTo(this->RotatableTop->GetComponentRotation(), TurretRot, DeltaTime, RotationSpeed);
	RotatableTop->SetWorldRotation(NewRot);
}

FHitResult ATurretActor::CheckIfAimingAtEnemy()
{
	FVector loc;
	FRotator rot;
	FHitResult hit;
	loc = BulletArrow->GetComponentLocation();
	rot = BulletArrow->GetComponentRotation();

	FVector start = loc + (rot.Vector() * 65);
	FVector end = loc + (rot.Vector() * FireRange);
	FCollisionQueryParams params;
	GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params);
	return hit;
}

void ATurretActor::fire()
{
	FActorSpawnParameters SpawnParams;
	AActor* ActorRef = GetWorld()->SpawnActor<AActor>(BulletClass, BulletArrow->GetComponentTransform());
	ActorRef->SetLifeSpan(2);
}

