//Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaceTarget.generated.h"

class USphereComponent;

UCLASS()
class GAME_API ARaceTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	ARaceTarget();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    USphereComponent* Sphere;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

};
