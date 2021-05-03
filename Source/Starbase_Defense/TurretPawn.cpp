// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

// Sets default values
ATurretPawn::ATurretPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 500;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	RotationArrow = CreateDefaultSubobject<UArrowComponent>(L"RotationArrow");
	RotationArrow->AttachTo(RootComponent);
	RotationArrow->RegisterComponent();
	BodyCylinder = CreateDefaultSubobject<UStaticMeshComponent>(L"Body");
	BodyCylinder->AttachTo(RootComponent);
	BodyCylinder->RegisterComponent();

	GunCone = CreateDefaultSubobject<UStaticMeshComponent>(L"Gun");
	GunCone->AttachTo(RotationArrow);
	GunCone->RegisterComponent();
	BulletArrow = CreateDefaultSubobject<UArrowComponent>(L"BulletArrow");
	BulletArrow->AttachTo(GunCone);
	BulletArrow->RegisterComponent();

}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurretPawn::fire, 0.1f, true);
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor* enemy = findClosestEnemy();
	if (enemy != nullptr && closestEnemy < 1200)
		RotateTowards(enemy->GetActorLocation(), DeltaTime);
	CheckIfAimingAtEnemy();
	if (enemy == nullptr) shooting = false;
}

// Called to bind functionality to input
void ATurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* ATurretPawn::findClosestEnemy()
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

void ATurretPawn::RotateTowards(FVector TargetLocation, float DeltaTime)
{
	FRotator TurretRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), FVector(TargetLocation.X, TargetLocation.Y, this->GetActorLocation().Z));
	FRotator NewRot = FMath::RInterpConstantTo(this->RotationArrow->GetComponentRotation(), TurretRot, DeltaTime, RotationSpeed);
	RotationArrow->SetWorldRotation(NewRot);
}

void ATurretPawn::CheckIfAimingAtEnemy()
{
	FVector loc;
	FRotator rot;
	FHitResult hit;
	loc = RotationArrow->GetComponentLocation();
	rot = RotationArrow->GetComponentRotation();

	FVector start = loc + (rot.Vector() * 200);
	FVector end = loc + (rot.Vector() * 1000);
	FCollisionQueryParams params;

	shooting = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params);
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" %d"), shooting));*/

	//DrawDebugLine(GetWorld(), start, end, FColor::Orange, false, 0.1f);
}

void ATurretPawn::fire()
{	
	if (BulletClass && shooting)
	{
		FActorSpawnParameters SpawnParams;
		AActor* ActorRef = GetWorld()->SpawnActor<AActor>(BulletClass, BulletArrow->GetComponentTransform());
		ActorRef->SetLifeSpan(2);
	}
}
