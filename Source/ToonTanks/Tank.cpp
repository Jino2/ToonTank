// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

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
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (TankPlayerController)
	{
		FHitResult TraceHitResult;
		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurret(HitLocation);

		//for debugging
		// DrawDebugSphere(GetWorld(), HitLocation, 15.f, 10, FColor::Red, false, -1.f);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
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
