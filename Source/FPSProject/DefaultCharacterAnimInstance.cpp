// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacterAnimInstance.h"
#include <cmath>

UDefaultCharacterAnimInstance::UDefaultCharacterAnimInstance()
{
	//initialize floats
	WalkRunBlend = 1.0f;
	StrideBlend = 0.0f;
	Speed = 0.0f;
	YawVelocityRotation = 0.0f;

	//initialize bools
	bMoving = false;

	//initialize enums
	Gait = EGait::RUNNING;
	MovementDirection = EMovementDirection::FORWARD;

	//initialize structs
	DirectionBlend = FDirectionBlend();

	//initialize curvs
	SpeedStrideBlendCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("SpeedStrideBlend"));
	DirectionBlendCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("DirectionBlend"));
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

	if (Speed < 1)
		bMoving = false;
	else
		bMoving = true;

	//set StrideBlend
	StrideBlend = SpeedStrideBlendCurve->GetFloatValue(Speed/100.0f);
}

void UDefaultCharacterAnimInstance::UpdateRotationValues(float DeltaSeconds)
{
	//Set YawRotation
	if (!bMoving)
		YawVelocityRotation = OwningActor->GetVelocity().ToOrientationRotator().Yaw - OwningActor->GetActorRotation().Yaw;
	else
		YawVelocityRotation = 0.0f;

	//Set MovementDirection
	if(-45.0f < YawVelocityRotation && YawVelocityRotation < 45.0f)
		MovementDirection = EMovementDirection::FORWARD;
	if (-135.0f < YawVelocityRotation && YawVelocityRotation < -45.0f)
		MovementDirection = EMovementDirection::LEFT;
	if (45.0f < YawVelocityRotation && YawVelocityRotation < 135.0f)
		MovementDirection = EMovementDirection::RIGHT;
	if (YawVelocityRotation < -135.0f || 135.0f < YawVelocityRotation)
		MovementDirection = EMovementDirection::BACKWARD;

	//set DirectionBlend
	DirectionBlend.f = DirectionBlendCurve->GetFloatValue(YawVelocityRotation/ 100.0f);
	DirectionBlend.fl = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+45.0f) / 100.0f);
	DirectionBlend.bl = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+135.0f) / 100.0f);
	DirectionBlend.b = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+180.0f) / 100.0f);
	DirectionBlend.br = DirectionBlendCurve->GetFloatValue((YawVelocityRotation-135.0f) / 100.0f);
	DirectionBlend.fr = DirectionBlendCurve->GetFloatValue((YawVelocityRotation-45.0f) / 100.0f);
}