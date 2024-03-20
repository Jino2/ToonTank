// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (InFireRange())
	{
		auto PlayerLocation = PlayerTank->GetActorLocation();
		RotateTurret(PlayerLocation);
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, 1 / FireRatePerSec, true,
	                                0.f);
}

void ATower::CheckFireCondition()
{
	if (InFireRange()) Fire();
}

bool ATower::InFireRange()
{
	auto PlayerLocation = PlayerTank->GetActorLocation();
	float Distance = FVector::Dist(PlayerLocation, GetActorLocation());
	return Distance < Range;
}
