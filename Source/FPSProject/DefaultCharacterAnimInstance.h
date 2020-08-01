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

UCLASS(transient, Blueprintable, BlueprintType, hideCategories = AnimInstance)
class FPSPROJECT_API UDefaultCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDefaultCharacterAnimInstance();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float walkRun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float stride;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGait Gait;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMovementDirection MovementDirection;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};