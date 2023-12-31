// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GOSPlayerController.generated.h"

class AGOSPlayerCharacter;
class UInputMappingContext;
class UInputAction;
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

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void FireWeapon();
	void ToggleWalkOrJog();
	void SetZoomWeaponView();
	void RevertToDefaultCameraView();
	void ReloadGame();
	void CommandAllyToFollow();
	void CommandAttackOrMoveToTargetPosition();
	void CommandFireAtWill();
	void CommandHoldFire();

private:
	bool bCanIssueCommand = true;

private:
	void HandleDelayNextCommandCompleted();
	void DelayNextCommand();
};
