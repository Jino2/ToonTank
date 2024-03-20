// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Range = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRatePerSec = 1.f;

	void HandleDestruction();
protected:
	virtual void BeginPlay() override;
	
private:
	class ATank* PlayerTank;
	
	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();
	bool InFireRange();
	
};
