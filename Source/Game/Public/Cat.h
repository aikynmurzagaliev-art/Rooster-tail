// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Cat.generated.h"

class ANPC;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UUserWidget;
struct FInputActionValue;

UCLASS()
class GAME_API ACat : public ACharacter
{
	GENERATED_BODY()

public:
	ACat();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TSubclassOf<UUserWidget> UIWidgetClass;

	UPROPERTY()
	UUserWidget* UIWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	//may be then
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY()
	AActor* CurrentInteractable;

	

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	void Interact();

public:
	void SetInteractable(AActor* NewInteractable);

protected:

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 700.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintCamera = 110.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkCamera = 90.f;

	float TargetFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FOVInterpSpeed = 10.f;
};