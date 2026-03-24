//Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressManager.generated.h"

class ACat;

UENUM(BlueprintType)
enum class EGameStage : uint8
{
    Start        UMETA(DisplayName = "Start"),
    Penguin      UMETA(DisplayName = "Penguin"),
    Deer         UMETA(DisplayName = "Deer"),
    Horse        UMETA(DisplayName = "Horse"),
    Final        UMETA(DisplayName = "Final"),
    Return       UMETA(DisplayName = "Return")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageChanged, EGameStage, NewStage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPageCollected, int32, TotalPages);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelCompleted);
//Race
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRaceStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRaceTimeUpdated, float, TimeLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRaceEnded, bool, bSuccess);

UCLASS()
class GAME_API AProgressManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AProgressManager();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    int32 Pages = 0;

    UPROPERTY(BlueprintReadOnly)
    int32 Grain = 0;

    bool bNPCGavePage = false;

    FTimerHandle RaceTimerHandle;
    bool bRaceActive = false;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
    float RaceTime = 10.f;

    UPROPERTY(BlueprintReadOnly)
    float CurrentRaceTime = 0.f;

    UPROPERTY(BlueprintAssignable)
    FOnRaceStarted OnRaceStarted;

    UPROPERTY(BlueprintAssignable)
    FOnRaceTimeUpdated OnRaceTimeUpdated;

    UPROPERTY(BlueprintAssignable)
    FOnRaceEnded OnRaceEnded;

public:
    //GameStage
    UPROPERTY(BlueprintReadOnly)
    EGameStage CurrentStage;

    UPROPERTY(BlueprintAssignable)
    FOnStageChanged OnStageChanged;

    UPROPERTY(BlueprintAssignable)
    FOnLevelCompleted OnLevelCompleted;

    UPROPERTY(BlueprintAssignable)
    FOnPageCollected OnPageCollected;

    EGameStage GetNextStage(EGameStage Stage) const;

    UFUNCTION(BlueprintCallable)
    void SetStage(EGameStage NewStage);

    UFUNCTION(BlueprintCallable)
    void AddPage();

    UFUNCTION(BlueprintCallable)
    void GoNextStage();

    UFUNCTION(BlueprintCallable)
    void AddGrain();

    UFUNCTION(BlueprintCallable)
    bool HasEnoughGrain(int32 Amount) const;

    UFUNCTION(BlueprintCallable)
    void StartRace();

    UFUNCTION()
    void UpdateRace();

    UFUNCTION()
    void EndRace(bool bSuccess);

    UFUNCTION()
    void HandleNPCInteracted(ACat* Player);

};
