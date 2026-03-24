//Kleith's Game

#pragma once

#include "Interactable.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Page.generated.h"

class AProgressManager;
class UBoxComponent;

UCLASS()
class GAME_API APage : public AActor, public IInteractable
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
	APage();

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
