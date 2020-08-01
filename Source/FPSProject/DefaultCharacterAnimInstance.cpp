// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacterAnimInstance.h"

UDefaultCharacterAnimInstance::UDefaultCharacterAnimInstance()
{
	WalkRunBlend = 1.0f;
	StrideBlend = 0.0f;
	Speed = 0.0f;
	YawRotation = 0.0f;

	Gait = EGait::RUNNING;
	MovementDirection = EMovementDirection::FORWARD;

	//SpeedStrideBlend = UCurveFloat(FObjectInitializer());
}

void UDefaultCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AActor* TryGetOwingActor = GetOwningActor();
	if (TryGetOwingActor != nullptr)
		OwningActor = TryGetOwingActor;

	UpdateMovementValues(DeltaSeconds);
	UpdateRotationValues(DeltaSeconds);
}

void UDefaultCharacterAnimInstance::UpdateMovementValues(float DeltaSeconds)
{
	//set Speed
	Speed = OwningActor->GetVelocity().Size();

	//set StrideBlend
	//StrideBlend = FFloatCurve().Evaluate(Speed);
	//StrideBlend = FFloatCurve().
	StrideBlend = Speed / 600;
}

void UDefaultCharacterAnimInstance::UpdateRotationValues(float DeltaSeconds)
{
	//Set YawRotation
	YawRotation = OwningActor->GetVelocity().Rotation().Yaw;

	//Set MovementDirection
	if(-45.0f < YawRotation && YawRotation < 45.0f)
		MovementDirection = EMovementDirection::FORWARD;
	if (-135.0f < YawRotation && YawRotation < -45.0f)
		MovementDirection = EMovementDirection::LEFT;
	if (45.0f < YawRotation && YawRotation < 135.0f)
		MovementDirection = EMovementDirection::RIGHT;
	if (YawRotation < -135.0f || 135.0f < YawRotation)
		MovementDirection = EMovementDirection::BACKWARD;
}