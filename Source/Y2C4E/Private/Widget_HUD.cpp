#include "Widget_HUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void UWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	
	if(HealthBar) { HealthBar->SetPercent(1); }
 
	if(ScoreText) { ScoreText->SetText(FText::FromString("Score: 0")); }
}
 
void UWidget_HUD::UpdateHealth(float newHealthRatio)
{
	UE_LOG(LogTemp, Display, TEXT("new raito is: %f"), newHealthRatio);
	if(HealthBar) { HealthBar->SetPercent(newHealthRatio); }
}
 
void UWidget_HUD::UpdateScore(int newScore)
{
	if(ScoreText)
	{
		ScoreText->SetText(
		   FText::FromString(
			  FString::Printf(TEXT("Score: %d"), newScore)
		   )
		);
	}
}

void UWidget_HUD::Win()
{
	FGenericPlatformMisc::RequestExit(false);
}
void UWidget_HUD::Loss()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UWidget_HUD::RestartLevel()
{
	UGameplayStatics::GetPlayerController(this, 0)->RestartLevel();
}