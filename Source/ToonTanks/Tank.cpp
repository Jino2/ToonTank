// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
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
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurret(HitLocation);

		//for debugging
		// DrawDebugSphere(GetWorld(), HitLocation, 15.f, 10, FColor::Red, false, -1.f);
	}
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

void ATank::RotateTurret(FVector LookAtTarget)
{
	// Update TurretMesh rotation to face LookAtTarget
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	LookAtRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		6.f
	);
	TurretMesh->SetWorldRotation(LookAtRotation);
}
