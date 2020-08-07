// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <cmath>

UDefaultCharacterAnimInstance::UDefaultCharacterAnimInstance()
{
	//initialize floats
	WalkRunBlend = 1.0f;
	StrideBlend = 0.0f;
	Speed = 0.0f;
	YawVelocityRotation = 0.0f;
	YawRotationRate = 0.0f;
	YawViewRotation = 0.0f;

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
	WalkRunBlendCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("WalkRunBlend"));
}

void UDefaultCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter == nullptr)
	{
		//initialize
		OwningCharacter = Cast<ADefaultCharacter>(GetOwningActor());
	}

	else
	{
		UpdateStates();
		UpdateMovementValues(DeltaSeconds);
		UpdateRotationValues(DeltaSeconds);
	}
}

void UDefaultCharacterAnimInstance::UpdateStates()
{
	if (OwningCharacter->bPressedSprint)
		Gait = EGait::SPRINTING;
	else if (OwningCharacter->bPressedWalk)
		Gait = EGait::WALKING;
	else
		Gait = EGait::RUNNING;
}

void UDefaultCharacterAnimInstance::UpdateMovementValues(float DeltaSeconds)
{
	//set Speed
	Speed = FVector(OwningCharacter->GetVelocity().GetComponentForAxis(EAxis::X), OwningCharacter->GetVelocity().GetComponentForAxis(EAxis::Y), 0.0f).Size();

	if (Speed < 1.0f)
		bMoving = false;
	else
		bMoving = true;

	//set StrideBlend
	StrideBlend = SpeedStrideBlendCurve->GetFloatValue(Speed/100.0f);

	//Set WalkRunBlend
	WalkRunBlend = WalkRunBlendCurve->GetFloatValue(static_cast<std::underlying_type<EGait>::type>(Gait));
}

void UDefaultCharacterAnimInstance::UpdateRotationValues(float DeltaSeconds)
{
	//set ViewRotation
	float OldYawViewRotation = YawViewRotation;
	YawViewRotation = OwningCharacter->GetViewRotation().Yaw;

	//set RotationRate
	YawRotationRate = (YawViewRotation - OldYawViewRotation)/DeltaSeconds;

	//set YawRotation
	if (bMoving)
	{
		float TryYawVelocityRotation = OwningCharacter->GetVelocity().Rotation().Yaw;

		//adjust the value so that it is between 0 and 360
		if (TryYawVelocityRotation < 0.0f)
			TryYawVelocityRotation += 360.0f;

		//make it relative
		TryYawVelocityRotation = TryYawVelocityRotation - YawViewRotation;

		//adjust the value so that it is between 0 and 360 again
		if (TryYawVelocityRotation < 0.0f)
			TryYawVelocityRotation += 360.0f;

		YawVelocityRotation = TryYawVelocityRotation;
	}

	else
		YawVelocityRotation = 0.0f;

	//set MovementDirection
	if (225.0f <= YawVelocityRotation && YawVelocityRotation < 315.0f)
		MovementDirection = EMovementDirection::LEFT;
	else if (45.0f < YawVelocityRotation && YawVelocityRotation <= 135.0f)
		MovementDirection = EMovementDirection::RIGHT;
	else if (YawVelocityRotation > 135.0f && 225.0f > YawVelocityRotation)
		MovementDirection = EMovementDirection::BACKWARD;
	else
		MovementDirection = EMovementDirection::FORWARD;


	//set DirectionBlend
	DirectionBlend.f = DirectionBlendCurve->GetFloatValue(YawVelocityRotation/ 100.0f);
	DirectionBlend.fl = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+45.0f) / 100.0f);
	DirectionBlend.bl = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+135.0f) / 100.0f);
	DirectionBlend.b = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+180.0f) / 100.0f);
	DirectionBlend.br = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+225.0f) / 100.0f);
	DirectionBlend.fr = DirectionBlendCurve->GetFloatValue((YawVelocityRotation+315.0f) / 100.0f);
}