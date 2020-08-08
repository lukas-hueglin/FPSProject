// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

UDefaultCharacterAnimInstance::UDefaultCharacterAnimInstance()
{
	//initialize floats
	WalkRunBlend = 1.0f;
	StrideBlend = 0.0f;
	Speed = 0.0f;
	YawVelocityDirection = 0.0f;

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

	//initialize vectors
	RelativeVelocityDirection = FVector();
	ViewDirection = FVector();

	//initialize rotators
	RotationRate = FRotator();
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
	// set ViewRotation
	ViewDirection = OwningCharacter->GetViewRotation().Vector();
	ViewDirection.Normalize();

	//Set Relative Direction
	FVector OldRelativeVelocityDirection = RelativeVelocityDirection;
	RelativeVelocityDirection = OwningCharacter->GetVelocity();
	RelativeVelocityDirection.Normalize();
	RelativeVelocityDirection = FRotator(RelativeVelocityDirection.Rotation() - ViewDirection.Rotation()).Vector();

	//set RotationRate
	RotationRate = RelativeVelocityDirection.Rotation() - OldRelativeVelocityDirection.Rotation();

	//set YawVelocityDirection
	YawVelocityDirection = RelativeVelocityDirection.Rotation().Yaw;

	//set MovementDirection
	if (-135.0f >= YawVelocityDirection && YawVelocityDirection < -45.0f)
		MovementDirection = EMovementDirection::LEFT;
	else if (45.0f < YawVelocityDirection && YawVelocityDirection <= 135.0f)
		MovementDirection = EMovementDirection::RIGHT;
	else if (YawVelocityDirection > 135.0f || -135.0f > YawVelocityDirection)
		MovementDirection = EMovementDirection::BACKWARD;
	else
		MovementDirection = EMovementDirection::FORWARD;

	DirectionBlend.f = FMath::Clamp<float>(RelativeVelocityDirection.X, 0.0f, 1.0f);
	DirectionBlend.b = FMath::Abs(FMath::Clamp<float>(RelativeVelocityDirection.X, -1.0f, 0.0f));
	DirectionBlend.l = FMath::Abs(FMath::Clamp<float>(RelativeVelocityDirection.Y, -1.0f, 0.0f));
	DirectionBlend.r = FMath::Clamp<float>(RelativeVelocityDirection.Y, 0.0f, 1.0f);
}