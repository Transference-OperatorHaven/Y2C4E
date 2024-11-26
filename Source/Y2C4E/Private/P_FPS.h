// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "Weapon_Base.h"
#include "GameFramework/Character.h"
#include "P_FPS.generated.h"

class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;
class UCapsuleComponent;

UCLASS(Abstract)
class Y2C4E_API AP_FPS : public ACharacter, public IInputable
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AP_FPS();
	
	UFUNCTION(BlueprintCallable)
	void resetWeapon();
	UFUNCTION(BlueprintCallable)
	void Winner();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _WeaponRef;

	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_ViewControl_Implementation(FVector2D value) override;
	virtual void Input_FirePress_Implementation() override;
	virtual void Input_FireRelease_Implementation() override;
	virtual void Input_JumpPress_Implementation() override;
	virtual void Input_JumpRelease_Implementation() override;
	virtual void Input_CrouchPress_Implementation() override;
	virtual void Input_CrouchRelease_Implementation() override;
	virtual void Input_ReloadPressed_Implementation() override;
	virtual void Input_MeleePressed_Implementation() override;
	virtual void Pickup_Implementation(TSubclassOf<AWeapon_Base> weapon) override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	virtual UBehaviorTree* GetBehaviourTree_Implementation() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Knife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> _Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;
private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
	
};
