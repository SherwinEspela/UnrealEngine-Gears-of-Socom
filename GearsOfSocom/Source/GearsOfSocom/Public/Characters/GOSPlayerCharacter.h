// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GOSBaseCharacter.h"
#include "Constants/UICustomEnums.h"
#include "GOSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AGOSAllyCharacter;
class USoundBase;
class UGOSPlayerAnimInstance;
class UWeaponWidget;
class UMemberStatusWidget;
class UMemberStatusComponent;

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
	virtual void ToggleCrouch() override;
	void ToggleWalkOrJog();
	void SetZoomWeaponView();
	void RevertToDefaultCameraView();
	void CommandFollow();
	void CommandAttackTo();
	void CommandAttackOrMoveToTargetPosition();
	void CommandFireAtWill();
	void CommandHoldFire();
	void CommandRegroup();
	void CommandAmbush();
	void CommandRunTo();
	void CommandStealthTo();
	void CommandHoldPosition();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool CheckIfAiming() const { return bIsAiming; }
	FORCEINLINE UMemberStatusComponent* GetMemberStatusComponent() { return MemberStatusComponent; }
	FORCEINLINE void SetSelectedGroupCommandType(EGroupCommandType GroupCommandType) { SelectedGroupCommandType = GroupCommandType; }

protected:
	virtual void BeginPlay() override;

protected:
	void ToggleCameraFOVInterp(float DeltaSeconds);
	void SetupTeam();

protected:
	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomWeaponValue = 40.f;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraDefaultFOV;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomWeaponSpeed = 20.f;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	bool bIsAiming = false;

	UPROPERTY(EditDefaultsOnly)
	UMemberStatusComponent* MemberStatusComponent;

protected:
	// Ally Bots / AI
	AGOSAllyCharacter* Boomer;
	AGOSAllyCharacter* Jester;
	AGOSAllyCharacter* Spectre;

	TArray<AGOSAllyCharacter*> Team;
	TArray<AGOSAllyCharacter*> BravoTeam;

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
	void MoveToTargetPosition(FVector TargetPosition);
	void PerformAllyCommandWithPrimaryType(EPrimaryCommandType CommandType);

	UFUNCTION(BlueprintCallable)
	void HandleCrouchingAnimationFinished();

private:
	float CurrentCameraFOV;
	UGOSPlayerAnimInstance* PlayerAnimInstance;
	EGroupCommandType SelectedGroupCommandType;
	bool bCrouchingMovementInProgress = false;
};
