// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstActor.h"

#include "MovieSceneSequenceID.h"
#include "MovieSceneTracksComponentTypes.h"
#include "Components/ArrowComponent.h"

AFirstActor::AFirstActor()
{
	//_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = _Root;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(RootComponent);

	

	//_RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement Component"));
}
void AFirstActor::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle ActorSpinHandle;
	//GetWorldTimerManager().SetTimer(ActorSpinHandle, this, &AFirstActor::RotateChange, _RotationDelay, false);
}

void AFirstActor::Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}
/*void AFirstActor::RotateChange()
{
	_RotatingMovementComponent->RotationRate = FRotator(0,180,0);
}*/