// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SlateWrapperTypes.h"
#include <PewPew/EFireModes.h>
#include <cstddef>
#include "PewPewCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class APewPewCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	const int MAX_MAGAZINE_AMMO_CAPACITY = 32;
	const int NUMBER_OF_MAGAZINES = 4;

	const float RELOAD_TIME = 2;

public:
	APewPewCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class APewPewProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/// <summary>
	/// To make sure the gun doesn't shoot 999 a second, we need a cooldown
	/// </summary>
	FTimerHandle WeaponTimerHandle;

	FTimerHandle ReloadTimerHandle;

protected:
	
	/** Fires a projectile. */
	void OnFireStart();

	void WhileFire();

	void OnFireStop();

	void OnReloadStart();

	void OnReloadStop();

	void OnFireModeChange();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:

	/** Returns Mesh1P sub object **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent sub object **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EFireModes FireMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int BurstAmmoUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MagazineAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int TotalRemainingAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isReloading;

	UFUNCTION(BlueprintCallable)
	int getMagazineAmmo() const { return MagazineAmmo; }

	UFUNCTION(BlueprintCallable)
	int getTotalRemainingAmmo() const { return TotalRemainingAmmo; }

	UFUNCTION(BlueprintCallable)
	bool getReloadingState() const { return isReloading; }

	UFUNCTION(BlueprintCallable)
	ESlateVisibility getReloadingVisibility() const { return isReloading ? ESlateVisibility::Visible : ESlateVisibility::Collapsed; }

	UFUNCTION(BlueprintCallable)
	FString getFireModeText() const
	{ 
		switch (FireMode)
		{
			case EFireModes::AUTO_FIRE:
				return FString("AUTO");

			case EFireModes::BURST_FIRE:
				return FString("BURST");

			case EFireModes::SINGLE_FIRE:
				return FString("SINGLE");
		}

		return FString("#ERROR_TEXT");
	}

};

