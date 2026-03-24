//Kleith's Game


#include "RoadLight.h"
#include "ProgressManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PointLightComponent.h"



ARoadLight::ARoadLight()
{
	PrimaryActorTick.bCanEverTick = true;
    Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
    Light->SetupAttachment(RootComponent);
}

void ARoadLight::BeginPlay()
{
    Super::BeginPlay();

    CachedManager = Cast<AProgressManager>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AProgressManager::StaticClass())
    );

    if (CachedManager)
    {
        CachedManager->OnStageChanged.AddDynamic(this, &ARoadLight::HandleStageChanged);
        CachedManager->OnLevelCompleted.AddDynamic(this, &ARoadLight::HandleLevelCompleted);
    }

    if (CachedManager)
    {
        HandleStageChanged(CachedManager->CurrentStage);
    }
	
}

void ARoadLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoadLight::TurnOn()
{
    Light->SetVisibility(true);
}

void ARoadLight::TurnOff()
{
    Light->SetVisibility(false);
}

void ARoadLight::HandleStageChanged(EGameStage NewStage)
{
    if (NewStage == ActiveStage)
    {
        TurnOn();
    }
    else
    {
        TurnOff();
    }
}

void ARoadLight::HandleLevelCompleted()
{
    
}