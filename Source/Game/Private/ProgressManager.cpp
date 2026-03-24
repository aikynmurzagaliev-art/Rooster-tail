//Kleith's Game


#include "ProgressManager.h"
#include "Kismet/GameplayStatics.h"
#include "NPC_Friend.h"

AProgressManager::AProgressManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AProgressManager::BeginPlay()
{
    Super::BeginPlay();
    SetStage(EGameStage::Start);

    TArray<AActor*> NPCs;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPC_Friend::StaticClass(), NPCs);

    for (AActor* Actor : NPCs)
    {
        ANPC_Friend* NPC = Cast<ANPC_Friend>(Actor);
        if (NPC)
        {
            NPC->OnNPCInteracted.AddDynamic(this, &AProgressManager::HandleNPCInteracted);
        }
    }
}

EGameStage AProgressManager::GetNextStage(EGameStage Stage) const
{
    switch (Stage)
    {
    case EGameStage::Start:
        return EGameStage::Penguin;

    case EGameStage::Penguin:
        return EGameStage::Deer;

    case EGameStage::Deer:
        return EGameStage::Horse;

    case EGameStage::Horse:
        return EGameStage::Final;

    case EGameStage::Final:
        return EGameStage::Return;

    default:
        return Stage;
    }
}

void AProgressManager::SetStage(EGameStage NewStage)
{
    CurrentStage = NewStage;
    OnStageChanged.Broadcast(NewStage);
}

void AProgressManager::AddPage()
{
    Pages++;
    OnPageCollected.Broadcast(Pages);

    SetStage(GetNextStage(CurrentStage));
}

void AProgressManager::GoNextStage()
{
    SetStage(GetNextStage(CurrentStage));
}

void AProgressManager::AddGrain()
{
    Grain++;
}

bool AProgressManager::HasEnoughGrain(int32 Amount) const
{
    return Grain >= Amount;
}

void AProgressManager::StartRace()
{
    bRaceActive = true;
    CurrentRaceTime = RaceTime;
    OnRaceStarted.Broadcast();

    GetWorld()->GetTimerManager().SetTimer(
        RaceTimerHandle,
        this,
        &AProgressManager::UpdateRace,
        0.1f,
        true
    );
}

void AProgressManager::UpdateRace()
{
    CurrentRaceTime -= 0.1f;
    OnRaceTimeUpdated.Broadcast(CurrentRaceTime);

    if (CurrentRaceTime <= 0.f)
    {
        EndRace(false);
    }
}

void AProgressManager::EndRace(bool bSuccess)
{
    if (!bRaceActive) return;

    bRaceActive = false;

    GetWorld()->GetTimerManager().ClearTimer(RaceTimerHandle);

    if (bSuccess)
    {
        OnRaceEnded.Broadcast(bSuccess);
    }
    else
    {
        OnRaceEnded.Broadcast(bSuccess);
    }
}

void AProgressManager::HandleNPCInteracted(ACat* Player)
{
    if (HasEnoughGrain(5) && !bNPCGavePage)
    {
        AddPage();
        bNPCGavePage = true;
    }
    if (CurrentStage == EGameStage::Horse) {

        AddPage();
    }
}


