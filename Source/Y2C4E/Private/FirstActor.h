// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "FirstActor.generated.h"

UCLASS(Abstract)
class Y2C4E_API AFirstActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstActor();
	virtual void BeginPlay() override;
	virtual void RotateChange();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Arrow;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URotatingMovementComponent> _RotatingMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++ Variables", meta = (AllowPrivateAccess = "true"))
	float _RotationDelay;
	
};