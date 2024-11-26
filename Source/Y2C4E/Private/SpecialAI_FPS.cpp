// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialAI_FPS.h"


// Sets default values
ASpecialAI_FPS::ASpecialAI_FPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpecialAI_FPS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpecialAI_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpecialAI_FPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


