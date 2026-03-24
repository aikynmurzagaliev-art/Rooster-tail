// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "NPC_Enemy.generated.h"

class USphereComponent;

UCLASS()
class GAME_API ANPC_Enemy : public ANPC
{
    GENERATED_BODY()

public:
    ANPC_Enemy();

    UFUNCTION(BlueprintCallable)
    void SetChasing(bool bNewChasing);

protected:
    virtual void BeginPlay() override;

    FTimerHandle ChaseTimerHandle;

    UFUNCTION()
    void UpdateChase();

    UPROPERTY(VisibleAnywhere)
    USphereComponent* KillSphere;

    UFUNCTION()
    void OnOverlapPlayer(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);


    bool bIsChasing = false;
};
