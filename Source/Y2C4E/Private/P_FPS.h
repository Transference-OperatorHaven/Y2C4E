// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputtable.h"
#include "GameFramework/Character.h"
#include "P_FPS.generated.h"

class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;
class UCapsuleComponent;

UCLASS(Abstract)
class Y2C4E_API AP_FPS : public ACharacter, public IInputtable
{
	GENERATED_BODY()
private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
public:
	// Sets default values for this character's properties
	AP_FPS();

	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_ViewControl_Implementation(FVector2D value) override;
	virtual void Input_FirePress_Implementation() override;
	virtual void Input_FireRelease_Implementation() override;
	virtual void Input_JumpPress_Implementation() override;
	virtual void Input_JumpRelease_Implementation() override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> _Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};