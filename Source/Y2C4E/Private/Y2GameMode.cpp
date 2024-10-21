// Fill out your copyright notice in the Description page of Project Settings.


#include "Y2GameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
 
AActor* AY2GameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_PlayerStarts.Num() == 0)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundActors);
		for(AActor* actor : foundActors)
		{
			_PlayerStarts.Add(actor);
		}
	}
	if(_PlayerStarts.Num() > 0)
	{
		return _PlayerStarts[FMath::RandRange(0, _PlayerStarts.Num()-1)];
	}
	return nullptr;
}
 
void AY2GameMode::PostLogin(APlayerController* NewPlayer)
{
	_PlayerControllers.AddUnique(NewPlayer);
	Super::PostLogin(NewPlayer);
}
 
void AY2GameMode::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}
 
void AY2GameMode::HandleMatchIsWaitingToStart()
{
	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);
	for(UActorComponent* comp : outComponents)
	{
		if(UGameRule* rule = Cast<UGameRule>(comp))
		{
			_GameRuleManagers.Add(rule);
			rule->Init();
			rule->OnComplete.AddUniqueDynamic(this, &AY2GameMode::Handle_GameRuleCompleted);
			rule->OnPointsScored.AddUniqueDynamic(this, &AY2GameMode::Handle_GameRulePointsScored);
			_GameRulesLeft++;
		}
	}
    
	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AY2GameMode::DecreaseCountdown, 1.f, false);
	Super::HandleMatchIsWaitingToStart();
}

void AY2GameMode::DecreaseCountdown()
{
	_CountdownTimer--;
	UE_LOG(LogTemp, Display, TEXT("GAMEMODE Countdown: %d"), _CountdownTimer);
	if(_CountdownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AY2GameMode::DecreaseCountdown, 1.f, false);
	}
}

void AY2GameMode::Handle_GameRuleCompleted()
{
	
}

void AY2GameMode::Handle_GameRulePointsScored(AController* scorer, int points)
{
	
}

void AY2GameMode::HandleMatchHasStarted()
{
	DefaultPawnClass = _MatchPawn;
	for(AController* controller : _PlayerControllers)
	{
		RestartPlayer(controller);
		UE_LOG(LogTemp, Display, TEXT("Spawning player") );
	}
	Super::HandleMatchHasStarted();
}
 
void AY2GameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}
 
void AY2GameMode::OnMatchStateSet()
{
	FString output;
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting To Start";
	}
	else if(MatchState == MatchState::InProgress)
	{
		output = "InProgress";
	}
	else if(MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting Post Match";
	}
	else if(MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}
 
	UE_LOG(LogTemp, Display, TEXT("MATCH STATE CHANGED: %s"), *output);
    
	Super::OnMatchStateSet();
}
 
bool AY2GameMode::ReadyToStartMatch_Implementation() { return false; }
 
bool AY2GameMode::ReadyToEndMatch_Implementation() { return false; }