// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DefaultCharacter.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DefaultCharacterAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGait : uint8
{
	WALKING		UMETA(DisplayName = "Walking"),
	RUNNING		UMETA(DisplayName = "Running"),
	SPRINTING	UMETA(DisplayName = "Sprinting"),
};

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	FORWARD		UMETA(DisplayName = "Forward"),
	RIGHT		UMETA(DisplayName = "Right"),
	LEFT		UMETA(DisplayName = "Left"),
	BACKWARD	UMETA(DisplayName = "Backward"),
};

UENUM(BlueprintType)
enum class EAssultRifleStates : uint8
{
	RELAXED	UMETA(DisplayName = "Relaxed"),
	READY		UMETA(DisplayName = "Ready"),
	AIMING		UMETA(DisplayName = "Aiming"),
};

UENUM(BlueprintType)
enum class EOverlayStates : uint8
{
	DEFAULT			UMETA(DisplayName = "Default"),
	ASSULTRIFLE		UMETA(DisplayName = "AssultRifle"),
};

USTRUCT(BlueprintType)
struct FDirectionBlend
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		float f = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float l = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float r = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float b = 0.0f;
};

USTRUCT(BlueprintType)
struct FLeanBlend
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		float RL = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float FB = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float Alpha = 0.0f;
};

UCLASS(transient, Blueprintable, BlueprintType, hideCategories = AnimInstance)
class FPSPROJECT_API UDefaultCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDefaultCharacterAnimInstance();

public:
	//blending value between walking and running
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float WalkRunBlend;

	//blending value which indicates the size of the steps
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float StrideBlend;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float YawVelocityDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float YawViewDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bRotateR;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bRotateL;

	std::vector<float> rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ADefaultCharacter* OwningCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EGait Gait;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EMovementDirection MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EAssultRifleStates AssultRifleStates;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EOverlayStates OverlayStates;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FDirectionBlend DirectionBlend;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FLeanBlend LeanBlend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* SpeedStrideBlendCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* WalkRunBlendCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector RelativeVelocityDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ViewDirection;
public:
	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
		void UpdateStates();
	UFUNCTION()
		void UpdateMovementValues(float DeltaSeconds);
	UFUNCTION()
		void UpdateRotationValues(float DeltaSeconds);
	UFUNCTION()
		void UpdateBlends();
};