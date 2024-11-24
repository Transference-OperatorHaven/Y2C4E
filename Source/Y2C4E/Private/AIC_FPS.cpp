// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_FPS.h"

#include "Inputable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionTypes.h"


// Sets default values
AAIC_FPS::AAIC_FPS()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIC_FPS::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
	{
		RunBehaviorTree(IInputable::Execute_GetBehaviourTree(InPawn));
	}
}


// Called every frame
void AAIC_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

