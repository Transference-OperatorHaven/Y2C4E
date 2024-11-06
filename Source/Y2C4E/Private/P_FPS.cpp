// Fill out your copyright notice in the Description page of Project Settings.


#include "P_FPS.h"

#include "HealthComponent.h"
#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AP_FPS::AP_FPS()
{
	UE_LOG(LogTemp, Display, TEXT("PAWN SPAWNED AND CONSTRUCTED"));
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);
	_Knife = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Knife"));
	_Knife->SetupAttachment(_Camera);
	
	_Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	_Collider->SetupAttachment(RootComponent);
	
}

void AP_FPS::resetWeapon()
{
	if(_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
		_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void AP_FPS::Handle_HealthDead(AController* causer)
{
	UE_LOG(LogTemp, Display, TEXT("PENIS"));
}

void AP_FPS::Handle_HealthDamaged(float current, float max, float change)
{
	UE_LOG(LogTemp, Display, TEXT("PENIS 2"));
}

void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	
	
	IInputtable::Input_Move_Implementation(value);
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), value.Y);
	AddMovementInput(_Camera->GetRightVector(), value.X);

}

void AP_FPS::Input_ViewControl_Implementation(FVector2D value)
{
	
	IInputtable::Input_ViewControl_Implementation(value);
	AddActorWorldRotation(FRotator(0.f, value.X, 0.f));
	if((_Camera->GetRelativeRotation().Pitch + value.Y) > 90.0f || (_Camera->GetRelativeRotation().Pitch + value.Y) < -90.0f)
	{
		//UE_LOG(LogTemp,Display, TEXT("The pitch is: %f and value.Y is %f so together they'd exceed limits"), _Camera->GetRelativeRotation().Pitch, value.Y);
		value.Y = 0;
	}	
	_Camera->AddLocalRotation(FRotator(value.Y, 0.f, 0.f));
	//UE_LOG(LogTemp, Display, TEXT("Value inputted is: %f %f"), value.X, value.Y);
}

void AP_FPS::Input_FirePress_Implementation()
{
	IInputtable::Input_FirePress_Implementation();
	if(_WeaponRef)
	{
		_WeaponRef->StartFire();
	}
}

void AP_FPS::Input_FireRelease_Implementation()
{
	IInputtable::Input_FireRelease_Implementation();
	if(_WeaponRef)
	{
		_WeaponRef->StopFire();
	}
}

void AP_FPS::Input_JumpPress_Implementation()
{
	ACharacter::Jump();
}

void AP_FPS::Input_JumpRelease_Implementation()
{
	ACharacter::StopJumping();
}

void AP_FPS::Input_CrouchPress_Implementation()
{
	ACharacter::Crouch();
	
}

void AP_FPS::Input_CrouchRelease_Implementation()
{
	ACharacter::UnCrouch();
}

void AP_FPS::Input_ReloadPressed_Implementation()
{
	IInputtable::Input_ReloadPressed_Implementation();
}

void AP_FPS::Input_MeleePressed_Implementation()
{
UE_LOG(LogTemp, Display, TEXT("Knifed"));
	IInputtable::Input_MeleePressed_Implementation();
	if(_Camera)
	{
		UWorld* const world = GetWorld();
		if(world == nullptr) { return; }
 
		FHitResult hit(ForceInit);
		FVector start = _Camera->GetComponentLocation();
		FVector end = start + (_Camera->GetForwardVector() * 300);
		TArray<AActor*> ActorsToIgnore;
 
		if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		   UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
		   ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red,
		   FLinearColor::Green, 5))
		{
			if(hit.GetActor() == this) { return; }
			UGameplayStatics::ApplyDamage(hit.GetActor(), 100,
			   GetOwner()->GetInstigatorController(), GetOwner(),
			   UDamageType::StaticClass());
 
       
			UE_LOG(LogTemp, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString())
		}
	}
}

void AP_FPS::Pickup_Implementation(AWeapon_Base* weapon)
{
	IInputtable::Pickup_Implementation(weapon);
	_DefaultWeapon = weapon;
	resetWeapon();
}

UInputMappingContext* AP_FPS::GetMappingContext_Implementation()
{
	return _InputMapping;
}

UBehaviorTree* AP_FPS::GetBehaviourTree_Implementation()
{
	return _BehaviorTree;
}

// Called when the game starts or when spawned
void AP_FPS::BeginPlay()
{
	Super::BeginPlay();

	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDead);

	if(_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
		_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	
}

// Called every frame
void AP_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AP_FPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

