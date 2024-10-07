// Fill out your copyright notice in the Description page of Project Settings.


#include "Y2PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inputtable.h"
#include "Kismet/KismetSystemLibrary.h"

void AY2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AY2PlayerController::Move);
		EnhancedInputComponent->BindAction(ViewControlAction, ETriggerEvent::Triggered, this, &AY2PlayerController::ViewControl);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AY2PlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AY2PlayerController::StopJumping);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AY2PlayerController::StartFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AY2PlayerController::StopFiring);
		
	}
}

void AY2PlayerController::Move(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2d>();
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputtable::StaticClass()))
		{
			IInputtable::Execute_Input_Move(currentPawn, MoveVector);
		}
	}
}

void AY2PlayerController::ViewControl(const FInputActionValue& value)
{
	FVector2D LookVector = value.Get<FVector2d>();
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputtable::StaticClass()))
		{
			IInputtable::Execute_Input_ViewControl(currentPawn, LookVector);
		}
	}
	
}

void AY2PlayerController::Jump()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputtable::StaticClass()))
		{
			IInputtable::Execute_Input_JumpPress(currentPawn);
		}
	}
}

void AY2PlayerController::StopJumping()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputtable::StaticClass()))
		{
			IInputtable::Execute_Input_JumpRelease(currentPawn);
		}
	}
}



void AY2PlayerController::StartFire()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputtable::StaticClass()))
		{
			IInputtable::Execute_Input_FirePress(currentPawn);
		}
	}
}

void AY2PlayerController::StopFiring()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputtable::StaticClass()))
		{
			IInputtable::Execute_Input_FireRelease(currentPawn);
		}
	}
}

void AY2PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UEnhancedInputLocalPlayerSubsystem* _subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputtable::StaticClass()))
		{
			_subsystem->AddMappingContext(IInputtable::Execute_GetMappingContext(InPawn), 0);
		}
	}
	
}