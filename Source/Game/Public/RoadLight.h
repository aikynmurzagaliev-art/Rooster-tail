//Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadLight.generated.h"

class AProgressManager;
class UPointLightComponent;

UCLASS()
class GAME_API ARoadLight : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Light")
	EGameStage ActiveStage;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;

	UPROPERTY()
	AProgressManager* CachedManager;

	ARoadLight();

protected:
	virtual void BeginPlay() override;
	virtual void TurnOn();
	virtual void TurnOff();

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void HandleStageChanged(EGameStage NewStage);

	UFUNCTION()
	void HandleLevelCompleted();
};
