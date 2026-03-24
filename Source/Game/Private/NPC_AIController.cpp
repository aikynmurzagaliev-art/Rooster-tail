//Kleith's Game

#include "NPC_AIController.h"
#include "NPC.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ANPC_AIController::ANPC_AIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void ANPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ANPC* NPCPawn = Cast<ANPC>(InPawn);
	if (NPCPawn && BehaviorTreeAsset)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTreeAsset->BlackboardAsset);
		RunBehaviorTree(BehaviorTreeAsset);
	}
}
