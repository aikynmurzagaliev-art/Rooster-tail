// Kleith's Game

#include "NPC_Friend.h"
#include "Components/SphereComponent.h"
#include "Cat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NPC_AIController.h"

ANPC_Friend::ANPC_Friend()
{
    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(RootComponent);


    InteractionSphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &ANPC_Friend::OnPlayerEnter
    );

    InteractionSphere->OnComponentEndOverlap.AddDynamic(
        this,
        &ANPC_Friend::OnPlayerExit
    );
    
}

void ANPC_Friend::OnPlayerEnter(
    UPrimitiveComponent* OverlappedComponent, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult& SweepResult)
{
    ACat* Player = Cast<ACat>(OtherActor);

    if (!Player) return;

    if (Player)
    {
        Player->SetInteractable(this);
    }

    //NPC stop
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon)
    {
        AICon->StopMovement();

        UBlackboardComponent* BB = AICon->GetBlackboardComponent();
        if (BB)
        {
            BB->SetValueAsBool("IsPlayerNearby", true);
        }
    }

    


    //press E
    bIsInteractable = true;
    ShowInteractWidget();
}

void ANPC_Friend::OnPlayerExit(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    ACat* Player = Cast<ACat>(OtherActor);

    if (!Player) return;

    if (Player)
    {
        Player->SetInteractable(nullptr);
    }

    //NPC move
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon)
    {
        UBlackboardComponent* BB = AICon->GetBlackboardComponent();
        if (BB)
        {
            BB->SetValueAsBool("IsPlayerNearby", false);  
        }
    }
    

    //press E
    bIsInteractable = false;
    ShowInteractWidget();

    //remove dialog
    if (bDialogueActive)
    {
        if (DialogueWidget)
        {
            DialogueWidget->RemoveFromParent();
            DialogueWidget = nullptr;
        }

        bDialogueActive = false;
        return;
    }
}

void ANPC_Friend::ShowInteractWidget()
{
    if (!InteractWidgetClass) return;

    if (bIsInteractable) 
    {
        InteractWidget = CreateWidget<UUserWidget>(
            GetWorld(),
            InteractWidgetClass
        );

        InteractWidget->AddToViewport();
        return;
    }

    InteractWidget->RemoveFromParent();
    InteractWidget = nullptr;
}

void ANPC_Friend::ShowDialogWidget()
{
    if (!DialogueWidgetClass) return;

    if (bDialogueActive)
    {
        //remove dialog
        if (DialogueWidget)
        {
            DialogueWidget->RemoveFromParent();
            DialogueWidget = nullptr;
            bHasInteracted = true;
        }

        bDialogueActive = false;
        return;
    }

    //show dialog
    DialogueWidget = CreateWidget<UUserWidget>(
        GetWorld(),
        DialogueWidgetClass
    );

    if (DialogueWidget)
    {
        
        DialogueWidget->AddToViewport();
        bDialogueActive = true;
    }
}

void ANPC_Friend::Interact_Implementation(ACat* Player)
{
    //NPC look at player
    FVector Direction = Player->GetActorLocation() - GetActorLocation();
    FRotator LookRotation = Direction.Rotation();

    SetActorRotation(FRotator(0.f, LookRotation.Yaw, 0.f));

    if(!bHasInteracted){ShowDialogWidget();}
    

    OnNPCInteracted.Broadcast(Player);
}
