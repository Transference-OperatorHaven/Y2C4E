// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInputable : public UInterface
{
	GENERATED_BODY()
};


class UInputMappingContext;

/**
 * 
 */
class Y2C4E_API IInputable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_ViewControl(FVector2D value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Move(FVector2D value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpPress();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpRelease();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_FirePress();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_FireRelease();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchPress();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchRelease();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_ReloadPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_MeleePressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Pickup(TSubclassOf<AWeapon_Base> weapon);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInputMappingContext* GetMappingContext();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UBehaviorTree* GetBehaviourTree();
};
