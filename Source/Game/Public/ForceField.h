// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForceField.generated.h"

UCLASS()
class GAME_API AForceField : public AActor
{
	GENERATED_BODY()
	
public:	
	AForceField();
	virtual void DisableBarrier();
};
