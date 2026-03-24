// Kleith's Game


#include "NPC.h"
#include "GameFramework/CharacterMovementComponent.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

