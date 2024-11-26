// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDeadSignature, AController*, causer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedSignature, float, newHealth, float, maxHealth, float, changeInHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class Y2C4E_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(BlueprintAssignable)
	FHealthDeadSignature OnDead;
	UPROPERTY(BlueprintAssignable)
	FHealthDamagedSignature OnDamaged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float _CurrentHealth;
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

	
private:
	//UFUNCTION()
	//UHealthComponent();
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,class AController* Instigator, AActor* DamageCauser);
	
};
