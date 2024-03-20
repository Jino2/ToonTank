// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnableState(false);
		}
	}
	else if (auto DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if(ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableDelegate, StartDelay, false);
	}
}
