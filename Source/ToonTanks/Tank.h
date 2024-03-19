// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Camera/CameraComponent.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	UPROPERTY(EditInstanceOnly, Category = "Movement")
	float MoveSpeed = 100.f;

	UPROPERTY(EditInstanceOnly, Category = "Movement")
	float TurnSpeed = 100.f;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Player Camera")
	UCameraComponent* PlayerCamera;
	
	void Move(float Value);
	void Turn(float Value);
	void RotateTurret(FVector LookAtTarget);

	APlayerController* PlayerControllerRef;
};
