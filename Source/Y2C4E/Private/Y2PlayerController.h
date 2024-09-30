// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Y2PlayerController.generated.h"


struct FInputActionValue;
class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class Y2C4E_API AY2PlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UPlayerInput> _DebugAction;

	virtual void SetupInputComponent() override;
	virtual void Debug(FInputActionValue value);
	void Jump();
	void StopJumping();
	void Move();
	void ViewControl();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* ViewControlAction;
	
};
