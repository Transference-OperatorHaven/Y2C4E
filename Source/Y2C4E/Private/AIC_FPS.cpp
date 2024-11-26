// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_FPS.h"

#include "AI_FPS.h"
#include "HealthComponent.h"
#include "Inputable.h"
#include "Y2PlayerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values


// Called when the game starts or when spawned


void AAIC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
	{
		RunBehaviorTree(IInputable::Execute_GetBehaviourTree(InPawn));
	}
}

void AAIC_FPS::Handle_OnDeath(AController* Causer)
{
	AAI_FPS* pawn = (AAI_FPS*)GetPawn();

	AY2PlayerController* player = Cast<AY2PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	player->IncrementScore();
	pawn->_WeaponRef->Destroy();
	pawn->Destroy();
	Destroy();
}

void AAIC_FPS::Handle_TargetPerceptionChanged( AActor* OtherActor, FAIStimulus Stimulus)
{
	
	if(OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		
		UBlackboardComponent* BBc = (UBlackboardComponent*)GetBlackboardComponent();
		BBc->SetValueAsObject(TEXT("TargetActor"),OtherActor);
		
		AAI_FPS* pawn  = (AAI_FPS*)GetPawn();
		pawn->_WeaponRef->canFire = true;
	}
}
void AAIC_FPS::Handle_TargetPerceptionForgotten(AActor* Actor)
{
	
	UBlackboardComponent* BBc = (UBlackboardComponent*)GetBlackboardComponent();
	BBc->ClearValue(TEXT("TargetActor"));
	AAI_FPS* pawn  = (AAI_FPS*)GetPawn();
	pawn->_WeaponRef->canFire = false;
}

AAIC_FPS::AAIC_FPS()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	
	_sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	_sightConfig->SightRadius = 1000;
	_sightConfig->LoseSightRadius = 2000;
	_sightConfig->PeripheralVisionAngleDegrees = 45;
	_sightConfig->SetMaxAge(2.0f);
	_sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	_sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	_sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	_AIPerception->ConfigureSense(*_sightConfig);
	_AIPerception->SetSenseEnabled(*_sightConfig->GetSenseImplementation(), true);

	
	_damageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	_damageConfig->SetMaxAge(5.0f);
	_AIPerception->ConfigureSense(*_damageConfig);
	_AIPerception->SetSenseEnabled(*_damageConfig->GetSenseImplementation(), true);

	_AIPerception->SetDominantSense(_sightConfig->GetSenseImplementation());
}

void AAIC_FPS::BeginPlay()
{
	Super::BeginPlay();

	_AIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIC_FPS::Handle_TargetPerceptionChanged);
	_AIPerception->OnTargetPerceptionForgotten.AddUniqueDynamic(this, &AAIC_FPS::Handle_TargetPerceptionForgotten);
	_AIPerception->SetActive(true);
	AAI_FPS* pawn  = (AAI_FPS*)GetPawn();
	pawn->_Health->OnDead.AddUniqueDynamic(this, &AAIC_FPS::Handle_OnDeath);
}

// Called every frame
void AAIC_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

