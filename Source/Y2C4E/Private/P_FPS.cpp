// Fill out your copyright notice in the Description page of Project Settings.


#include "P_FPS.h"

#include "HealthComponent.h"
#include "NavigationSystemTypes.h"
#include "Y2PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AP_FPS::AP_FPS()
{
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


	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDead);
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
	if(Cast<AY2PlayerController>(GetController())) {Cast<AY2PlayerController>(GetController())->_HUDWidget->Loss();}
}

void AP_FPS::Handle_HealthDamaged(float current, float max, float change)
{
	UE_LOG(LogTemp, Display, TEXT("health MAM"));
	if(Cast<AY2PlayerController>(GetController())) {Cast<AY2PlayerController>(GetController())->_HUDWidget->UpdateHealth(_Health->_CurrentHealth/_Health->_MaxHealth);}
}

void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	
	
	IInputable::Input_Move_Implementation(value);
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), value.Y);
	AddMovementInput(_Camera->GetRightVector(), value.X);

}

void AP_FPS::Input_ViewControl_Implementation(FVector2D value)
{
	
	IInputable::Input_ViewControl_Implementation(value);
	AddActorWorldRotation(FRotator(0.f, value.X, 0.f));
	if((_Camera->GetRelativeRotation().Pitch + value.Y) > 90.0f || (_Camera->GetRelativeRotation().Pitch + value.Y) < -90.0f)
	{
		value.Y = 0;
	}	
	_Camera->AddLocalRotation(FRotator(value.Y, 0.f, 0.f));
}

void AP_FPS::Input_FirePress_Implementation()
{
	IInputable::Input_FirePress_Implementation();
	if(_WeaponRef)
	{
		_WeaponRef->StartFire();
	}
}

void AP_FPS::Input_FireRelease_Implementation()
{
	IInputable::Input_FireRelease_Implementation();
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
	IInputable::Input_ReloadPressed_Implementation();
}

void AP_FPS::Input_MeleePressed_Implementation()
{
	IInputable::Input_MeleePressed_Implementation();
	if(_Camera)
	{
		UWorld* const world = GetWorld();
		if(world == nullptr) { return; }
 
		FHitResult hit(ForceInit);
		FVector start = _Camera->GetComponentLocation();
		FVector end = start + (_Camera->GetForwardVector() * 300);
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		
		if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		   UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
		   ActorsToIgnore, EDrawDebugTrace::None, hit, true, FLinearColor::Red,
		   FLinearColor::Green, 5))
		{
			UGameplayStatics::ApplyDamage(hit.GetActor(), 100,
			   GetOwner()->GetInstigatorController(), GetOwner(),
			   UDamageType::StaticClass());
		}
	}
}

void AP_FPS::Pickup_Implementation(TSubclassOf<AWeapon_Base> weapon)
{
	IInputable::Pickup_Implementation(weapon);
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
	if(_Health->OnDamaged.IsBound()) { UE_LOG(LogTemp,Display, TEXT("WHAT"));}
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

void AP_FPS::Winner()
{
	UE_LOG(LogTemp, Display, TEXT("stpid bird design"));
	if(Cast<AY2PlayerController>(GetController())) {Cast<AY2PlayerController>(GetController())->_HUDWidget->Win();}
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

