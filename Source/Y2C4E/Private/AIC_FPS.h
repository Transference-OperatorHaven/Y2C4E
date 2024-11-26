// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAISenseConfig_Sight* _sightConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAISenseConfig_Damage* _damageConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAIPerceptionComponent> _AIPerception;
	
	UFUNCTION()
	virtual void Handle_OnDeath(AController* Causer);
	UFUNCTION()
	void Handle_TargetPerceptionChanged(AActor* OtherActor, FAIStimulus Stimulus);
	UFUNCTION()
	void Handle_TargetPerceptionForgotten(AActor* Actor);
	
	

private:
};
