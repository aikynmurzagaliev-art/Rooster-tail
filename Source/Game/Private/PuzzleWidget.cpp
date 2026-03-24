// Kleith's Game

#include "PuzzleWidget.h"

void UPuzzleWidget::CloseWidget()
{
	
}

void UPuzzleWidget::SelectCorrect()
{
	OnAnswerSelected.Broadcast(true);
}

void UPuzzleWidget::SelectWrong()
{
	OnAnswerSelected.Broadcast(false);
}
