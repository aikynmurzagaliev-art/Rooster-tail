// Kleith's Game

#include "Cat.h"
#include "Interactable.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"

ACat::ACat()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
	

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

}

void ACat::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	TargetFOV = WalkCamera;
}

void ACat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACat::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACat::Look);

		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACat::StartJump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACat::StopJump);

		EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &ACat::StartSprint);
		EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACat::StopSprint);

		EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &ACat::Interact);
	}
}

void ACat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float NewFOV = FMath::FInterpTo(
		Camera->FieldOfView, 
		TargetFOV, 
		DeltaTime, 
		FOVInterpSpeed
	);

	Camera->SetFieldOfView(NewFOV);
}


void ACat::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, MovementVector.Y);
		AddMovementInput(Right, MovementVector.X);
	}
}

void ACat::Look(const FInputActionValue& Value)
{
	FVector2D LookAxis = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

void ACat::StartJump()
{
	Jump();
}

void ACat::StopJump()
{
	StopJumping();
}


void ACat::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	TargetFOV = SprintCamera;
}

void ACat::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	TargetFOV = WalkCamera;
}

void ACat::Interact()
{
	if (CurrentInteractable &&
		CurrentInteractable->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_Interact(CurrentInteractable, this);
	}
	
}

void ACat::SetInteractable(AActor* NewInteractable)
{
	CurrentInteractable = NewInteractable;
}