#include "Weapon_Base.h"

#include "ScreenPass.h"
#include "Components/ArrowComponent.h"

AWeapon_Base::AWeapon_Base()
{
    PrimaryActorTick.bCanEverTick = false;
    _FireDelay = 0.f;
    _currentMagAmmo = _maxMagAmmo;
 
    _Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = _Root;
 
    _Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    _Mesh->SetupAttachment(RootComponent);
 
    _Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
    _Muzzle->SetupAttachment(_Mesh);
}
 
void AWeapon_Base::StartFire()
{
    if(_currentMagAmmo > 0 && !_reloadTimer.IsValid())
    {
        Fire();
        if(_FireDelay != 0.f) //if theres a delay between shots
        {
            GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeapon_Base::Fire, _FireDelay, true);
        }
    }
    else
    {
        if(!_reloadTimer.IsValid())
        {
            GetWorld()->GetTimerManager().SetTimer(_reloadTimer, this, &AWeapon_Base::Reload, _reloadTime, false);
        }
    }
}
 
void AWeapon_Base::StopFire()
{
    GetWorld()->GetTimerManager().ClearTimer(_FireDelayTimer);
}
 
void AWeapon_Base::Fire()
{
    if(_currentMagAmmo > 0)
    {
        OnFire.Broadcast();
        _currentMagAmmo--;
    }
}

void AWeapon_Base::Reload()
{
    _currentMagAmmo = _maxMagAmmo;
    GetWorld()->GetTimerManager().ClearTimer(_reloadTimer);
}
