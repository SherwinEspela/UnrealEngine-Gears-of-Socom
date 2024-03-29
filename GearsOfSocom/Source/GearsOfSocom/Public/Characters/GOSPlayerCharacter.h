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
class ATargetLocationPinActor;
class UWeaponRapidFireComponent;
class UTeamMateReportComponent;

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
	void WeaponFirePress();
	void WeaponFireRelease();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool CheckIfAiming() const { return bIsAiming; }
	FORCEINLINE UMemberStatusComponent* GetMemberStatusComponent() { return MemberStatusComponent; }
	FORCEINLINE void SetSelectedGroupCommandType(EGroupCommandType GroupCommandType) { SelectedGroupCommandType = GroupCommandType; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetWalkSpeed() { return WALK_SPEED; }

protected:
	virtual void BeginPlay() override;

protected:
	void ToggleCameraFOVInterp(float DeltaSeconds);
	void InterpCameraBoomPositions(float DeltaSeconds);
	void SetupTeam();
	void HandleRapidShootPressed() override;

protected:
	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomFOV = 30.f;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraDefaultFOV;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomWeaponSpeed = 20.f;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	bool bIsAiming = false;

	UPROPERTY(EditDefaultsOnly)
	UMemberStatusComponent* MemberStatusComponent;

	UPROPERTY(EditAnywhere)
	UWeaponRapidFireComponent* WeaponRapidFireComponent;

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

	UPROPERTY(EditDefaultsOnly, Category = "Team Mate Report")
	UTeamMateReportComponent* TeamMateReportComponent;

protected:
	// UI
	UPROPERTY(EditAnywhere, Category = "Interface")
	TSubclassOf<UWeaponWidget> WeaponWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Interface")
	UWeaponWidget* WeaponWidget;

protected:
	// Target Location Pin guide
	void PlaceTargetLocationPin(FVector TargetPosition);

	UPROPERTY(EditAnywhere, Category = "Target Location Guide")
	TSubclassOf<ATargetLocationPinActor> TargetLocationPinClass;

	UPROPERTY(BlueprintReadOnly, Category = "Target Location Guide")
	ATargetLocationPinActor* TargetLocationPin;

protected:
	UPROPERTY(EditAnywhere, Category = "Control Sensitivity")
	float UserAimLookSensitivity = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Control Sensitivity")
	float UserAimMoveSensibility = 0.3f;

	float AimLookSensibility = 1.f;
	float AimMoveSensibility = 1.f;

protected:
	// Camera Positions
	UPROPERTY(EditAnywhere, Category = "Camera Positions")
	FVector CameraBoomPositionStanding;

	UPROPERTY(EditAnywhere, Category = "Camera Positions")
	FVector CameraBoomPositionStandingAiming;

	UPROPERTY(EditAnywhere, Category = "Camera Positions")
	FVector CameraBoomPositionCrouching;

	UPROPERTY(EditAnywhere, Category = "Camera Positions")
	FVector CameraBoomPositionCrouchingAiming;

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

	FVector CurrentCameraBoomPosition;
};
