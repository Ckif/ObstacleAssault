// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();


}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += PlatformVelocity*DeltaTime;
	SetActorLocation(CurrentLocation);
	const float Distance = FVector::Dist(StartLocation, CurrentLocation);

	if(Distance > MoveDistance)
	{
	const float Overshoot = Distance - MoveDistance;
		const FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection*MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity  = -PlatformVelocity;
	UE_LOG(LogTemp, Display, TEXT("Overshoot of %s: X = %f"), *this->GetName(), Overshoot);
	}
}

