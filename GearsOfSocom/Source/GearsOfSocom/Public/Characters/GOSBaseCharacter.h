// Copyright 2023 Sherwin Espela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Constants/Constants.h"
#include "GOSBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;
class UGOSBaseAnimInstance;
struct FInputActionValue;

UCLASS()
class GEARSOFSOCOM_API AGOSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	AGOSBaseCharacter();

	virtual void Tick(float DeltaSeconds) override;

public:
	// Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

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

public:
	UFUNCTION(BlueprintCallable)
	EMovementType GetMovementType() const;

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool CheckIfAiming() const { return bIsAiming; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ToggleWalkOrJog();
	void FireWeapon();
	void SetZoomWeaponView();
	void RevertToDefaultCameraView();
	void ToggleCameraFOVInterp(float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere, Category = Movement)
	float JogSpeedMultiplier = 1.2f;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomWeaponValue = 30.f;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraDefaultFOV;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CameraZoomWeaponSpeed = 20.f;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	bool bIsAiming = false;

protected:
	// Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	UAnimMontage* MontageFireWeapon;

private:
	EMovementType MovementType = EMovementType::EMT_Jog;
	float CurrentCameraFOV;

	UGOSBaseAnimInstance* GOSAnimInstance;
};
