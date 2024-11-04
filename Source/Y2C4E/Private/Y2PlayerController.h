// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_HUD.h"
#include "GameFramework/PlayerController.h"
#include "Y2PlayerController.generated.h"

class UWidget_HUD;
struct FInputActionValue;
class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class Y2C4E_API AY2PlayerController : public APlayerController, public IInterface
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UWidget_HUD> _HUDWidget;
 
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _ViewControlAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _FireAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _CroucAction;
	
	virtual void SetupInputComponent() override;
	
	void Move(const FInputActionValue& value);
	void ViewControl(const FInputActionValue& value);
	void Jump();
	void StopJumping();
	void StartFire();
	void StopFiring();
	void StartCrouching();
	void StopCrouching();

	virtual void OnPossess(APawn* InPawn) override;
	
	/*UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* ViewControlAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* FireAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputAction* JumpAction;*/

	

	
	
};
