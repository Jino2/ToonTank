// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void HandleDestruction();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess = "true"))
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	void RotateTurret(FVector LookAtTarget);
	void Fire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<AProjectile> ProjectileClass;
	
};
