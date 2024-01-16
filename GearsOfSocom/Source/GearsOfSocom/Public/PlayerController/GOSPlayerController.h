// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GOSPlayerController.generated.h"

class AGOSPlayerCharacter;
class UInputMappingContext;
class UInputAction;
class UCommandsWidget;
class UEnhancedInputComponent;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	AGOSPlayerCharacter* PlayerCharacter;

protected:
	// Player Inputs
	UPROPERTY(EditDefaultsOnly, Category = "Player Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleWalkOrJogAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* FireWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ZoomWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ReloadGameAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* CommandAllyToFollowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* CommandAttackOrMoveToTargetAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* CommandFireAtWillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* CommandHoldFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleCrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleShowCommandMenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectCommandAboveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectCommandBelowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectCommandLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectCommandRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectCommandAction;

protected:
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UCommandsWidget> CommandMenuWidgetClass;

	UCommandsWidget* CommandMenuWidget;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void FireWeapon();
	void ToggleWalkOrJog();
	void SetZoomWeaponView();
	void RevertToDefaultCameraView();
	void ReloadGame();
	void ToggleCrouch();

	void CommandAllyToFollow();
	void CommandAttackOrMoveToTargetPosition();
	void CommandFireAtWill();
	void CommandHoldFire();

	void ToggleShowCommandMenu();
	void SelectCommandAbove();
	void SelectCommandBelow();
	void SelectCommandLeft();
	void SelectCommandRight();
	void ChooseCommand();

private:
	bool bCanIssueCommand = true;
	UEnhancedInputComponent* EnhancedInputComponent;

private:
	void HandleDelayNextCommandCompleted();
	void DelayNextCommand();
	void SetupCommandInputs() const;

	UFUNCTION()
	void HandleCommandRequested(EGroupCommandType SelectedGroupCommandType, EPrimaryCommandType SelectedPrimaryCommandType);
};
