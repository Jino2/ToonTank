// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
	AddActorLocalOffset(
		FVector::ForwardVector * Value * MoveSpeed * GetWorld()->DeltaTimeSeconds,
		true,
		nullptr,
		ETeleportType::None
	);
}

void ATank::Turn(float Value)
{
	FRotator NewRotation = FRotator(0, Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0);
	AddActorLocalRotation(
		NewRotation,
		true,
		nullptr,
		ETeleportType::None
	);
}
