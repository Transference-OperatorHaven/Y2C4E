// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
 
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_InputFire.generated.h"
 
UCLASS()
class Y2C4E_API UBTTask_InputFire : public UBTTaskNode
{
	GENERATED_BODY()
 
public:
	UBTTask_InputFire();
 
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
 
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key_Pawn;
};