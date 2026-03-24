// Kleith's Game

#include "AltarPuzzle.h"
#include "PuzzleWidget.h"
#include "ForceField.h"
#include "Blueprint/UserWidget.h"
#include "Cat.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProgressManager.h"

AAltarPuzzle::AAltarPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(
		this,
		&AAltarPuzzle::OnPlayerEnter
	);

	BoxCollision->OnComponentEndOverlap.AddDynamic(
		this,
		&AAltarPuzzle::OnPlayerExit
	);
}

void AAltarPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

void AAltarPuzzle::OnPlayerEnter(
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

	Player->SetInteractable(this);

	bIsInteractable = true;
	ShowInteractWidget();
}

void AAltarPuzzle::OnPlayerExit(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	ACat* Player = Cast<ACat>(OtherActor);
	if (!Player) return;

	Player->SetInteractable(nullptr);

	bIsInteractable = false;
	CloseIntercatWidget();
}

void AAltarPuzzle::ShowInteractWidget()
{
	if (!InteractWidgetClass) return;

	if (bIsInteractable)
	{
		if (!InteractWidget)
		{
			InteractWidget = CreateWidget<UUserWidget>(
				GetWorld(),
				InteractWidgetClass
			);

			if (InteractWidget)
			{
				InteractWidget->AddToViewport();
			}
		}
	}
}

void AAltarPuzzle::CloseIntercatWidget()
{
	if (!InteractWidgetClass) return;
	
	if (InteractWidget)
		{
			InteractWidget->RemoveFromParent();
			InteractWidget = nullptr;
		}
}

void AAltarPuzzle::Interact_Implementation(ACat* Player)
{
	if (bPuzzleSolved || Attempts >= MaxAttempts)
	{
		ClosePuzzleWidget();
		return;
	}

	if (CurrentWidget)
	{
		ClosePuzzleWidget();
		ShowInteractWidget();
	}
	else
	{
		ShowPuzzleWidget();
		CloseIntercatWidget();
	}
}

void AAltarPuzzle::ShowPuzzleWidget()
{
	if (!PuzzleWidgetClass) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	CurrentWidget = CreateWidget<UPuzzleWidget>(PC, PuzzleWidgetClass);
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport();
		CurrentWidget->OnAnswerSelected.AddDynamic(this, &AAltarPuzzle::HandleAnswer);

		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}

void AAltarPuzzle::ClosePuzzleWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;

		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			PC->SetInputMode(FInputModeGameOnly());
			PC->bShowMouseCursor = false;
		}
	}
}

void AAltarPuzzle::HandleAnswer(bool bIsCorrect)
{
	Attempts++;

	if (bIsCorrect)
	{
		bPuzzleSolved = true;
		OnPuzzleSolved();
	}
	else if (Attempts >= MaxAttempts)
	{
		OnPuzzleFailed();
	}

	ClosePuzzleWidget();
}

void AAltarPuzzle::OnPuzzleSolved()
{
	if (LinkedBarrier)
	{
		LinkedBarrier->DisableBarrier();
		OnSolved.Broadcast(true);
	}
}

void AAltarPuzzle::OnPuzzleFailed()
{
	AProgressManager* Manager = Cast<AProgressManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AProgressManager::StaticClass())
	);

	if(Manager)
	{
		Manager->GoNextStage();
		OnSolved.Broadcast(false);
	}
}
