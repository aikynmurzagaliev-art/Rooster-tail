// Kleith's Game

#pragma once

#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AltarPuzzle.generated.h"

class AForceField;
class UPuzzleWidget;
class UBoxComponent;
class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSolved, bool, bSuccess);

UCLASS()
class GAME_API AAltarPuzzle : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AAltarPuzzle();

protected:
	UPROPERTY(BlueprintAssignable)
	FOnSolved OnSolved;

	virtual void BeginPlay() override;

	virtual void Interact_Implementation(ACat* Player) override;

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

	UFUNCTION()
	void HandleAnswer(bool bIsCorrect);

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void ClosePuzzleWidget();

	void ShowInteractWidget();
	void CloseIntercatWidget();
	void ShowPuzzleWidget();
	void OnPuzzleSolved();
	void OnPuzzleFailed();

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UPROPERTY()
	UUserWidget* InteractWidget;

	bool bIsInteractable = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Puzzle")	
	int32 Attempts = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Puzzle")	
	int32 MaxAttempts = 3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPuzzleWidget> PuzzleWidgetClass;

	UPROPERTY()
	UPuzzleWidget* CurrentWidget;

	UPROPERTY(EditAnywhere)
	AForceField* LinkedBarrier;

	// Проверка, можно ли еще открывать виджет
	bool bPuzzleSolved = false;
};