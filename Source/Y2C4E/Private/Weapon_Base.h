// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"
 
class UArrowComponent;
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);
 
UCLASS(Abstract)
class Y2C4E_API AWeapon_Base : public AActor
{
	GENERATED_BODY()
 
public:
	AWeapon_Base();
 
	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;
    
	void  StartFire();
	void StopFire();
    
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
    
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
	FTimerHandle _FireDelayTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int _currentMagAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _maxMagAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _reloadTime;
	FTimerHandle _reloadTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canFire;
	bool isFiring;
	

	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void Fire();
	UFUNCTION()
	virtual void FireDelayFinish();
	UFUNCTION()
	virtual void Reload();
};