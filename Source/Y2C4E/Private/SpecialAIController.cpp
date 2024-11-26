// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialAIController.h"

#include "Y2PlayerController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpecialAIController::ASpecialAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpecialAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpecialAIController::Tick(float DeltaTime)
{
	
}


void ASpecialAIController::Handle_OnDeath(AController* Causer)
{
	ASpecialAIController* pawn = (ASpecialAIController*)GetPawn();

	AY2PlayerController* player = Cast<AY2PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	player->_HUDWidget->Loss();
	
}
