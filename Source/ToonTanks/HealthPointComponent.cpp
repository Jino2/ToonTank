// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPointComponent.h"

// Sets default values for this component's properties
UHealthPointComponent::UHealthPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthPointComponent::DamageTaken(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;
	CurrentHealthPoint -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), CurrentHealthPoint);
}

// Called when the game starts
void UHealthPointComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealthPoint = MaxHealthPoint;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthPointComponent::DamageTaken);
}


// Called every frame
void UHealthPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

