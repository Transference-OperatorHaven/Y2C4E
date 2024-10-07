// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputtable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInputtable : public UInterface
{
	GENERATED_BODY()
};


class UInputMappingContext;

/**
 * 
 */
class Y2C4E_API IInputtable
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
	vo
	id Input_FirePress();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_FireRelease();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInputMappingContext* GetMappingContext();
};
