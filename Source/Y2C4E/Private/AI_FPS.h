// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P_FPS.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"
#include "AI_FPS.generated.h"

class UAIPerceptionComponent;

UCLASS(Abstract)
class Y2C4E_API AAI_FPS : public AP_FPS
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_FPS();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void Handle_OnDeath(AController* Causer);
	UFUNCTION()
	void Handle_TargetPerceptionChanged(AActor* OtherActor, FAIStimulus Stimulus);
	UFUNCTION()
	void Handle_TargetPerceptionForgotten(AActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAISenseConfig_Sight* _sightConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAIPerceptionComponent> _AIPerception;

private:
	
};
