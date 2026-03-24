// Kleith's Game

#pragma once

#include "Interactable.h"
#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "NPC.h"
#include "NPC_Friend.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNPCInteracted, ACat*, Player);

class USphereComponent;

UCLASS()
class GAME_API ANPC_Friend : public ANPC, public IInteractable
{
	GENERATED_BODY()
	
	ANPC_Friend();
private:
    bool bDialogueActive = false;
    bool bIsInteractable = false;

    bool bHasInteracted = false;     
    bool bHasGivenPage = false;      


protected:
    

    UPROPERTY(VisibleAnywhere)
    USphereComponent* InteractionSphere;

    UPROPERTY(EditAnywhere, Category = "Interact")
    TSubclassOf<UUserWidget> DialogueWidgetClass;

    UPROPERTY()
    UUserWidget* DialogueWidget;

    UPROPERTY(EditAnywhere, Category = "Interact")
    TSubclassOf<UUserWidget> InteractWidgetClass;

    UPROPERTY()
    UUserWidget* InteractWidget;

public:

    UPROPERTY(BlueprintAssignable, Category = "Event")
    FOnNPCInteracted OnNPCInteracted;

protected:
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

    virtual void ShowInteractWidget();
    virtual void ShowDialogWidget();
    virtual void Interact_Implementation(ACat* Player) override;
};
