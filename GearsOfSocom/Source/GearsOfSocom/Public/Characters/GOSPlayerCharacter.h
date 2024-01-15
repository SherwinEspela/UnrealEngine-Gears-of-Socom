// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "GOSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AGOSAllyCharacter;
class USoundBase;
class UGOSPlayerAnimInstance;
class UWeaponWidget;

/**
 * 
 */
UCLASS()
class GEARSOFSOCOM_API AGOSPlayerCharacter : public AGOSBaseCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	AGOSPlayerCharacter();

	virtual void Tick(float DeltaSeconds) override;

public:
	// Player Actions and Movement
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void FireWeapon() override;
	void ToggleWalkOrJog();
	void ToggleCrouch();
	void SetZoomWeaponView();
	void RevertToDefaultCameraView();
	void CommandAllyToFollow();
	void CommandAttackOrMoveToTargetPosition();
	void CommandFireAtWill();
	void CommandHoldFire();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool CheckIfAiming() const { return bIsAiming; }
	FORCEINLINE void SetAlly1(TObjectPtr<AGOSAllyCharacter> NewAlly) { Ally1 = NewAlly; }

protected:
	virtual void BeginPlay() override;

protected:
	void ToggleCameraFOVInterp(float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomWeaponValue = 40.f;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraDefaultFOV;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomWeaponSpeed = 20.f;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	bool bIsAiming = false;

protected:
	// Ally Bots / AI
	TObjectPtr<AGOSAllyCharacter> Ally1;

protected:
	// Voice Commands
	UPROPERTY(EditAnywhere, Category = "Voice Command")
	USoundBase* SFXCommandFollow;

	UPROPERTY(EditAnywhere, Category = "Voice Command")
	USoundBase* SFXCommandAttack;

	UPROPERTY(EditAnywhere, Category = "Voice Command")
	USoundBase* SFXCommandMoveToPosition;

	UPROPERTY(EditAnywhere, Category = "Voice Command")
	USoundBase* SFXCommandFireAtWill;

	UPROPERTY(EditAnywhere, Category = "Voice Command")
	USoundBase* SFXCommandHoldFire;

protected:
	// UI
	UPROPERTY(EditAnywhere, Category = "Interface")
	TSubclassOf<UWeaponWidget> WeaponWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Interface")
	UWeaponWidget* WeaponWidget;

private:
	void PlayAllyFollowResponseSound();
	void PlayAllyAttackEnemyResponseSound();
	void PlayAllyMoveToTargetResponseSound();
	void PlayAllyConfirmResponseSound();

private:
	float CurrentCameraFOV;
	UGOSPlayerAnimInstance* PlayerAnimInstance;
};
