// Fill out your copyright notice in the Description page of Project Settings.


#include "Y2PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HealthComponent.h"
#include "Inputable.h"
#include "P_FPS.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetSystemLibrary.h"

void AY2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &AY2PlayerController::Move);
		EnhancedInputComponent->BindAction(_ViewControlAction, ETriggerEvent::Triggered, this, &AY2PlayerController::ViewControl);
		EnhancedInputComponent->BindAction(_JumpAction, ETriggerEvent::Started, this, &AY2PlayerController::Jump);
		EnhancedInputComponent->BindAction(_JumpAction, ETriggerEvent::Completed, this, &AY2PlayerController::StopJumping);
		EnhancedInputComponent->BindAction(_FireAction, ETriggerEvent::Started, this, &AY2PlayerController::StartFire);
		EnhancedInputComponent->BindAction(_FireAction, ETriggerEvent::Completed, this, &AY2PlayerController::StopFiring);
		EnhancedInputComponent->BindAction(_CrouchAction, ETriggerEvent::Started, this, &AY2PlayerController::StartCrouching);
		EnhancedInputComponent->BindAction(_CrouchAction, ETriggerEvent::Completed, this, &AY2PlayerController::StopCrouching);
		EnhancedInputComponent->BindAction(_ReloadAction, ETriggerEvent::Started, this, &AY2PlayerController::Reload);
		EnhancedInputComponent->BindAction(_MeleeAction, ETriggerEvent::Completed, this, &AY2PlayerController::Melee);
		
	}
}



void AY2PlayerController::BeginPlay()
{
	Super::BeginPlay();
 
	if(_HUDWidgetClass)
	{
       _HUDWidget = CreateWidget<UWidget_HUD, AY2PlayerController*>( this, _HUDWidgetClass.Get());
		_HUDWidget->AddToViewport();
		_HUDWidget->UpdateScore(_Score);
		
		
	}
}

void AY2PlayerController::IncrementScore()
{ 
	_Score++;
	_HUDWidget->UpdateScore(_Score);
	_HUDWidget->UpdateHealth(Cast<AP_FPS>(GetPawn())->_Health->_CurrentHealth/Cast<AP_FPS>(GetPawn())->_Health->_MaxHealth);

}


void AY2PlayerController::Move(const FInputActionValue& value)
{

	FVector2D MoveVector = value.Get<FVector2d>();
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(currentPawn, MoveVector);
		}
	}
}

void AY2PlayerController::ViewControl(const FInputActionValue& value)
{
	FVector2D LookVector = value.Get<FVector2d>();
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_ViewControl(currentPawn, LookVector);
		}
	}
	
}

void AY2PlayerController::Jump()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpPress(currentPawn);
		}
	}
}

void AY2PlayerController::StopJumping()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpRelease(currentPawn);
		}
	}
}



void AY2PlayerController::StartFire()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FirePress(currentPawn);
		}
	}
}

void AY2PlayerController::StopFiring()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FireRelease(currentPawn);
		}
	}
}

void AY2PlayerController::StartCrouching()
{
	
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchPress(currentPawn);
		}
	}
}

void AY2PlayerController::StopCrouching()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchRelease(currentPawn);
		}
	}
}

void AY2PlayerController::Reload()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_ReloadPressed(currentPawn);
		}
	}
}

void AY2PlayerController::Melee()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_MeleePressed(currentPawn);
		}
	}
}

void AY2PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(UEnhancedInputLocalPlayerSubsystem* _subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
		{
			_subsystem->AddMappingContext(IInputable::Execute_GetMappingContext(InPawn), 0);
		}
	}
}
