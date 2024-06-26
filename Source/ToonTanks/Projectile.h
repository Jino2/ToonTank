// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category="Movement")
	UProjectileMovementComponent* ProjectileMovementComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess = "true"))
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, Category="Combat", meta=(AllowPrivateAccess = "true"))
	UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Damage")
	float Damage = 20.f;
};
