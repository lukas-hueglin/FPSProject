// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

USTRUCT(BlueprintType)
struct FDirectionBlend
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		float f = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float fl = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float bl = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float b = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float br = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float fr = 0.0f;
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
		float YawVelocityRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float YawAimingRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AActor* OwningActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EGait Gait;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EMovementDirection MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FDirectionBlend DirectionBlend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* SpeedStrideBlendCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* DirectionBlendCurve;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateMovementValues(float DeltaSeconds);
	void UpdateRotationValues(float DeltaSeconds);
};