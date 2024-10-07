// Fill out your copyright notice in the Description page of Project Settings.


#include "P_FPS.h"

#include "HealthComponent.h"
#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AP_FPS::AP_FPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	_Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	_Collider->SetupAttachment(RootComponent);
	
}

void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	
	UE_LOG(LogTemp, Display, TEXT("not smelly"));
	IInputtable::Input_Move_Implementation(value);
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), value.Y);
	AddMovementInput(_Camera->GetRightVector(), value.X);
}

void AP_FPS::Input_ViewControl_Implementation(FVector2D value)
{
	UE_LOG(LogTemp, Display, TEXT("Smelly"));
	IInputtable::Input_ViewControl_Implementation(value);
	AddActorWorldRotation(FRotator(0.f, value.X, 0.f));
	
	_Camera->AddLocalRotation(FRotator(value.Y, 0.f, 0.f));
}

void AP_FPS::Input_FirePress_Implementation()
{
	IInputtable::Input_FirePress_Implementation();
}

void AP_FPS::Input_FireRelease_Implementation()
{
	IInputtable::Input_FireRelease_Implementation();
}

void AP_FPS::Input_JumpPress_Implementation()
{
	IInputtable::Input_JumpPress_Implementation();
}

void AP_FPS::Input_JumpRelease_Implementation()
{
	IInputtable::Input_JumpRelease_Implementation();
}

UInputMappingContext* AP_FPS::GetMappingContext_Implementation()
{
	return _InputMapping;
}

// Called when the game starts or when spawned
void AP_FPS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AP_FPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

