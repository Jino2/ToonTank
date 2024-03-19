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
private:
	UPROPERTY(VisibleAnywhere, Category = "Player Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Player Camera")
	UCameraComponent* PlayerCamera;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void Move(float Value);
	void Turn(float Value);
};
