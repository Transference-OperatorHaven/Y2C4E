// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FPS.h"

#include "AIController.h"
#include "AIC_FPS.h"
#include "HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"


// Sets default values
AAI_FPS::AAI_FPS()
{
	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned


void AAI_FPS::Handle_OnDeath(AController* Causer)
{
	_WeaponRef->Destroy();
	Destroy();
}

void AAI_FPS::Handle_TargetPerceptionChanged( AActor* OtherActor, FAIStimulus Stimulus)
{
	if(OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		AAIC_FPS* controller = Cast<AAIC_FPS>(this->GetController());
		UBlackboardComponent* BBc = controller->GetBlackboardComponent();
		BBc->SetValueAsObject(TEXT("TargetActor"),OtherActor);

		_WeaponRef->canFire = true;
	}
}
void AAI_FPS::Handle_TargetPerceptionForgotten(AActor* Actor)
{
	AAIC_FPS* controller = Cast<AAIC_FPS>(this->GetController());
	UBlackboardComponent* BBc = controller->GetBlackboardComponent();
	BBc->ClearValue(TEXT("TargetActor"));
	
	_WeaponRef->canFire = false;
}

void AAI_FPS::BeginPlay()
{
	Super::BeginPlay();

	_AIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAI_FPS::Handle_TargetPerceptionChanged);
	_AIPerception->OnTargetPerceptionForgotten.AddUniqueDynamic(this, &AAI_FPS::Handle_TargetPerceptionForgotten);
	_Health->OnDead.AddUniqueDynamic(this, &AAI_FPS::Handle_OnDeath);
	
}

// Called every frame
void AAI_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAI_FPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
