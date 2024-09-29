// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstActor.h"

#include "MovieSceneSequenceID.h"
#include "MovieSceneTracksComponentTypes.h"
#include "Components/ArrowComponent.h"

AFirstActor::AFirstActor()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_Root);

	_RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement Component"));
}


