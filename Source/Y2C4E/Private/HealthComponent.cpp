// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	_MaxHealth = 100.f;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
	// ...
	
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	const float change = FMath::Min(_CurrentHealth, Damage);
	_CurrentHealth -= change;
	UE_LOG(LogTemp, Display, TEXT("Damage taken: %f, %f"), change, _CurrentHealth);
	if(_CurrentHealth <= 0.f)
	{
		OnDead.Broadcast(Instigator);
	}
}

