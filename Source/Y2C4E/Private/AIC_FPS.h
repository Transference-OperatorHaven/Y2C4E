// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_FPS.generated.h"

UCLASS(Abstract)
class Y2C4E_API AAIC_FPS : public AAIController
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AAIC_FPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	virtual void OnPossess(APawn* InPawn) override;


private:
};
