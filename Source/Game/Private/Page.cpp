//Kleith's Game

#include "Page.h"
#include "Cat.h"
#include "Components/BoxComponent.h"
#include "ProgressManager.h"
#include "Kismet/GameplayStatics.h"

APage::APage()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(
		this, 
		&APage::OnPlayerEnter
	);

	BoxCollision->OnComponentEndOverlap.AddDynamic(
		this,
		&APage::OnPlayerExit
	);
}

void APage::BeginPlay()
{
	Super::BeginPlay();
	
	CachedManager = Cast<AProgressManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AProgressManager::StaticClass())
	);
}

void APage::Interact_Implementation(ACat* Player)
{
	Collect();
}

void APage::OnPlayerEnter(
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

void APage::OnPlayerExit(
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

void APage::ShowInteractWidget()
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

void APage::Collect()
{
	if (CachedManager)
	{
		CachedManager->AddPage();
	}
	Destroy();
}
