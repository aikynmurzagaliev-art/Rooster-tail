// Kleith's Game


#include "NPC_Enemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Cat.h"
#include "AIController.h"

ANPC_Enemy::ANPC_Enemy()
{
    KillSphere = CreateDefaultSubobject<USphereComponent>(TEXT("KillSphere"));
    KillSphere->SetupAttachment(RootComponent);
}

void ANPC_Enemy::BeginPlay()
{
    Super::BeginPlay();

    KillSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC_Enemy::OnOverlapPlayer);
}

void ANPC_Enemy::UpdateChase()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AAIController* AICon = Cast<AAIController>(GetController());

    if (AICon && PlayerPawn)
    {
        AICon->MoveToActor(PlayerPawn, 50.f);
    }
}

void ANPC_Enemy::SetChasing(bool bNewChasing)
{
    bIsChasing = bNewChasing;

    if (bIsChasing)
    {
        GetWorld()->GetTimerManager().SetTimer(
            ChaseTimerHandle,
            this,
            &ANPC_Enemy::UpdateChase,
            0.2f,
            true
        );
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(ChaseTimerHandle);
    }
}

void ANPC_Enemy::OnOverlapPlayer(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    ACat* Player = Cast<ACat>(OtherActor);
    if (!Player) return;

    UE_LOG(LogTemp, Warning, TEXT("Player caught!"));

}

