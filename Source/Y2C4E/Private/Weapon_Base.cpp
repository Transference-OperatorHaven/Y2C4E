#include "Weapon_Base.h"

#include "ScreenPass.h"
#include "Components/ArrowComponent.h"

AWeapon_Base::AWeapon_Base()
{
    PrimaryActorTick.bCanEverTick = false;
    _FireDelay = 0.f;
    
 
    _Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = _Root;
 
    _Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    _Mesh->SetupAttachment(RootComponent);
 
    _Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
    _Muzzle->SetupAttachment(_Mesh);
}

void AWeapon_Base::BeginPlay()
{
    Super::BeginPlay();
    _currentMagAmmo = _maxMagAmmo;
}
 
void AWeapon_Base::StartFire()
{
    if(_currentMagAmmo > 0 && !_reloadTimer.IsValid())
    {
        canFire = true;
        isFiring = true;
        if(!GetWorldTimerManager().IsTimerActive(_FireDelayTimer)) //if theres a delay between shots
        {
            Fire();
        }
    }
    else
    {
        if(!_reloadTimer.IsValid())
        {
            canFire = false;
            FRotator rotator = FRotator::ZeroRotator;
            rotator.Pitch = 60.f;
            rotator.Roll = 20.f;
            _Mesh->SetRelativeRotation(rotator);
            GetWorld()->GetTimerManager().SetTimer(_reloadTimer, this, &AWeapon_Base::Reload, _reloadTime, false);
        }
    }
}
 
void AWeapon_Base::StopFire()
{
    canFire = false;
    isFiring = false;
}
 
void AWeapon_Base::Fire()
{
    if(_currentMagAmmo > 0)
    {
        GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeapon_Base::FireDelayFinish, _FireDelay, true);
        OnFire.Broadcast();
        _currentMagAmmo--;
    }
    else
    {
        if(!_reloadTimer.IsValid())
        {
            canFire = false;
            FRotator rotator = FRotator::ZeroRotator;
            rotator.Pitch = 60.f;
            rotator.Roll = 20.f;
            _Mesh->SetRelativeRotation(rotator);
            GetWorld()->GetTimerManager().SetTimer(_reloadTimer, this, &AWeapon_Base::Reload, _reloadTime, false);
        }
    }
}

void AWeapon_Base::FireDelayFinish()
{
    if(canFire)
    {
        
        Fire();
    }
}


void AWeapon_Base::Reload()
{
    _currentMagAmmo = _maxMagAmmo;
    _Mesh->SetRelativeRotation(FRotator::ZeroRotator);
    GetWorld()->GetTimerManager().ClearTimer(_reloadTimer);
    if(isFiring) canFire = true;
}
