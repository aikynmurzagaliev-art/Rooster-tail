// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuzzleWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnswerSelected, bool, bIsCorrect);

UCLASS()
class GAME_API UPuzzleWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAnswerSelected OnAnswerSelected;

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

	UFUNCTION(BlueprintCallable)
	void SelectCorrect();

	UFUNCTION(BlueprintCallable)
	void SelectWrong();
};
