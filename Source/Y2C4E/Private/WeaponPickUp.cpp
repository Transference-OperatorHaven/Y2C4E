// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickUp.h"

#include "MovieSceneSequenceID.h"
#include "NavigationSystemTypes.h"
#include "P_FPS.h"


// Sets default values
AWeaponPickUp::AWeaponPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = _Collision;
	_WeaponModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Model"));
	_WeaponModel->SetupAttachment(_Collision);
	_Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickUp::OnOverlapBegin);
	_Collision->OnComponentEndOverlap.AddDynamic(this, &AWeaponPickUp::OnOverlapEnd);
}

void AWeaponPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent , int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{	
	IInputtable::Pickup(_Weapon);	
}

void AWeaponPickUp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void AWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

