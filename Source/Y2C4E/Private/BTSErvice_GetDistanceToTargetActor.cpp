#include "BTService_GetDistanceToTargetActor.h"
 
#include "BehaviorTree/BlackboardComponent.h"
 
UBTService_GetDistanceToTargetActor::UBTService_GetDistanceToTargetActor()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;
 
	Key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, Key_Pawn), AActor::StaticClass());
	Key_TargetActor.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, Key_TargetActor), AActor::StaticClass());
	Key_Distance.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, Key_Distance));
}
 
void UBTService_GetDistanceToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
 
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		Key_Pawn.ResolveSelectedKey(*BBAsset);
		Key_TargetActor.ResolveSelectedKey(*BBAsset);
		Key_Distance.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_GetDistanceToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                    float DeltaSeconds)
{
	
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	AActor* b = Cast<AActor>(BBComp->GetValueAsObject(Key_TargetActor.SelectedKeyName));
	if(b == NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("target actor null"));
		return;
	}
	AActor* a = Cast<AActor>(BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName));
	if(a == NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("key pawn null"));
		return;
	}
	
	float distance = (a->GetActorLocation() - b->GetActorLocation()).Length();
	BBComp->SetValueAsFloat(Key_Distance.SelectedKeyName, distance);
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
