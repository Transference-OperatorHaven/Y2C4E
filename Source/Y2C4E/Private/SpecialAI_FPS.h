// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_FPS.h"
#include "SpecialAI_FPS.generated.h"

UCLASS()
class Y2C4E_API ASpecialAI_FPS : public AAI_FPS
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpecialAI_FPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
