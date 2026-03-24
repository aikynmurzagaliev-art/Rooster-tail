// Kleith's Game


#include "Grain.h"
#include "Cat.h"
#include "Components/BoxComponent.h"
#include "ProgressManager.h"
#include "Kismet/GameplayStatics.h"

AGrain::AGrain()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(
		this,
		&AGrain::OnPlayerEnter
	);

	BoxCollision->OnComponentEndOverlap.AddDynamic(
		this,
		&AGrain::OnPlayerExit
	);

}

void AGrain::BeginPlay()
{
	Super::BeginPlay();
	CachedManager = Cast<AProgressManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AProgressManager::StaticClass())
	);
}

void AGrain::Interact_Implementation(ACat* Player)
{
	Collect();
}

void AGrain::OnPlayerEnter(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	ACat* Player = Cast<ACat>(OtherActor);
	if (!Player) return;

	if (Player)
	{
		Player->SetInteractable(this);
	}


	bIsInteractable = true;
	ShowInteractWidget();

}

void AGrain::OnPlayerExit(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	ACat* Player = Cast<ACat>(OtherActor);

	if (!Player) return;

	if (Player)
	{
		Player->SetInteractable(nullptr);
	}

	bIsInteractable = false;
	ShowInteractWidget();

}

void AGrain::ShowInteractWidget()
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

void AGrain::Collect()
{
	if (CachedManager)
	{
		CachedManager->AddGrain();
	}
	Destroy();
}