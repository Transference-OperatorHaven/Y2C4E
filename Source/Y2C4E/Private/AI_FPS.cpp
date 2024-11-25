// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FPS.h"

#include "AIController.h"
#include "AIC_FPS.h"
#include "HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"


// Sets default values
AAI_FPS::AAI_FPS()
{
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned




void AAI_FPS::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AAI_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAI_FPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
