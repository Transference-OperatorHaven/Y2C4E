// Fill out your copyright notice in the Description page of Project Settings.


#include "Y2PlayerController.h"
#include "EnhancedInputComponent.h"

void AY2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AY2PlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AY2PlayerController::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AY2PlayerController::Move);
		EnhancedInputComponent->BindAction(ViewControlAction, ETriggerEvent::Triggered, this, &AY2PlayerController::ViewControl);
	}
}

void AY2PlayerController::Debug(FInputActionValue value)
{
	
}


void AY2PlayerController::Jump()
{
	
}

void AY2PlayerController::StopJumping()
{
	
}

void AY2PlayerController::Move()
{
	
}

void AY2PlayerController::ViewControl()
{
	
}
