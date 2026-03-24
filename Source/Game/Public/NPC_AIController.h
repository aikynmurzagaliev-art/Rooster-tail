//Kleith's Game

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"


UCLASS()
class GAME_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ANPC_AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* BlackboardComp;
};
