// Kleith's Game

#pragma once

#include "Blueprint/UserWidget.h"
#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grain.generated.h"

class AProgressManager;
class UBoxComponent;

UCLASS()
class GAME_API AGrain : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY()
	AProgressManager* CachedManager;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UPROPERTY()
	UUserWidget* InteractWidget;

	bool bIsInteractable = false;
	
public:	
	AGrain();

protected:
	virtual void BeginPlay() override;
    virtual void Interact_Implementation(class ACat* Player) override;
    virtual void Collect();
    virtual void ShowInteractWidget();


    UFUNCTION()
    void OnPlayerEnter(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    UFUNCTION()
    void OnPlayerExit(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );

};
