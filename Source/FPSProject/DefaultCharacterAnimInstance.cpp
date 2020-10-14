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
	RotationRate = 0.0f;
	SpeedMultiplier = 1.0f;

	//initialize bools
	bMoving = false;
	bRotateR = false;
	bRotateL = false;

	//initialize enums
	Gait = EGait::RUNNING;
	MovementDirection = EMovementDirection::FORWARD;
	AssultRifleStates = EAssultRifleStates::RELAXED;
	OverlayStates = EOverlayStates::DEFAULT;

	//initialize structs
	DirectionBlend = FDirectionBlend();
	LeanBlend = FLeanBlend();

	//initialize curvs
	SpeedStrideBlendCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("SpeedStrideBlend"));
	WalkRunBlendCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("WalkRunBlend"));

	//initialize vectors
	RelativeVelocityDirection = FVector();
	ViewDirection = FVector();
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
		UpdateBlends();
	}
}

void UDefaultCharacterAnimInstance::UpdateStates()
{
	if (OwningCharacter->bPressedSprint && OwningCharacter->bCanSprint)
	{
		Gait = EGait::SPRINTING;
		AssultRifleStates = EAssultRifleStates::RELAXED;
	}
	else if (OwningCharacter->bPressedWalk)
	{
		Gait = EGait::WALKING;
		AssultRifleStates = EAssultRifleStates::READY;
	}
	else
	{
		Gait = EGait::RUNNING;
		AssultRifleStates = EAssultRifleStates::READY;
	}

	if (OwningCharacter->ActiveEquipmentSlot == EActiveEquipmentSlot::NONE)
		OverlayStates = EOverlayStates::DEFAULT;
	else
		OverlayStates = EOverlayStates::ASSULTRIFLE;

	if (OwningCharacter->bAiming)
		AssultRifleStates = EAssultRifleStates::AIMING;
	else if (!OwningCharacter->bAiming && Gait != EGait::SPRINTING)
		AssultRifleStates = EAssultRifleStates::READY;
}

void UDefaultCharacterAnimInstance::UpdateMovementValues(float DeltaSeconds)
{
	//update Speed
	Speed = FVector(OwningCharacter->GetVelocity().GetComponentForAxis(EAxis::X), OwningCharacter->GetVelocity().GetComponentForAxis(EAxis::Y), 0.0f).Size();

	if (Speed < 1.0f)
		bMoving = false;
	else
		bMoving = true;

	//update MaxWalkingSpeed
	if (Gait == EGait::WALKING)
		OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = 165.0f*SpeedMultiplier;
	if (Gait == EGait::RUNNING)
		OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = 350.0f * SpeedMultiplier;
	if (Gait == EGait::SPRINTING)
		OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f * SpeedMultiplier;
}

void UDefaultCharacterAnimInstance::UpdateRotationValues(float DeltaSeconds)
{
	//Update YawViewDirection
	float OldYawViewDirection = YawViewDirection;
	YawViewDirection = OwningCharacter->GetControlRotation().Yaw;
	
	//update ViewRotation
	FVector OldViewDirection = ViewDirection;
	ViewDirection = OwningCharacter->GetControlRotation().Vector();
	ViewDirection.Normalize();

	//update Relative Direction
	FVector XYViewDirection = ViewDirection;
	XYViewDirection.SetComponentForAxis(EAxis::Z, 0.0f);

	if (bMoving)
		RelativeVelocityDirection = OwningCharacter->GetVelocity();
	else
		RelativeVelocityDirection = FVector(1.0f, 0.0f, 0.0f);

	RelativeVelocityDirection.Normalize();
	RelativeVelocityDirection = XYViewDirection.Rotation().UnrotateVector(RelativeVelocityDirection);
	RelativeVelocityDirection.Normalize();

	/*update RotationRate
	float GeneratedRotationRate = ((YawViewDirection - OldYawViewDirection) / (DeltaSeconds*1000))*1000;
	GeneratedRotationRate = FMath::SmoothStep(-180.0f, 180.0f, RotationRate) * 2 - 1;
	rotation.push_back(0);
	rotation[0] = GeneratedRotationRate;
	RotationRate = (rotation[0] + rotation[1] + rotation[2] + rotation[3] + rotation[4] + rotation[5]) / 6;*/
	//RotationRate = OwningCharacter->InputComponent->GetAxisValue(FName("Turn"));


	//update YawVelocityDirection
	YawVelocityDirection = RelativeVelocityDirection.Rotation().Yaw;

	//update MovementDirection
	if (-134.0f >= YawVelocityDirection && YawVelocityDirection <= -46.0f)
		MovementDirection = EMovementDirection::LEFT;
	else if (44.0f <= YawVelocityDirection && YawVelocityDirection <= 136.0f)
		MovementDirection = EMovementDirection::RIGHT;
	else if (YawVelocityDirection > 136.0f || -134.0f > YawVelocityDirection)
		MovementDirection = EMovementDirection::BACKWARD;
	else
		MovementDirection = EMovementDirection::FORWARD;
	DirectionBlend.f = FMath::Clamp<float>(RelativeVelocityDirection.X, 0.0f, 1.0f);
	DirectionBlend.b = FMath::Abs(FMath::Clamp<float>(RelativeVelocityDirection.X, -1.0f, 0.0f));
	DirectionBlend.l = FMath::Abs(FMath::Clamp<float>(RelativeVelocityDirection.Y, -1.0f, 0.0f));
	DirectionBlend.r = FMath::Clamp<float>(RelativeVelocityDirection.Y, 0.0f, 1.0f);
	
	//update rotation bools
	if (!bMoving)
	{
		if (RotationRate == 0.0f)
		{
			bRotateR = false;
			bRotateL = false;
		}
		else if (RotationRate < 0.0f)
		{
			bRotateL = true;
			bRotateR = false;
		}

		else if (RotationRate > 0.0f)
		{
			bRotateR = true;
			bRotateL = false;
		}
	}
	else
	{
		bRotateR = false;
		bRotateL = false;
	}

}

void UDefaultCharacterAnimInstance::UpdateBlends()
{
	//update StrideBlend
	StrideBlend = SpeedStrideBlendCurve->GetFloatValue(Speed);

	//update Leanblends
	LeanBlend.FB = (FMath::SmoothStep(-600, 600, RelativeVelocityDirection.X * Speed) * 2 - 1) / 2;
	LeanBlend.RL = FMath::SmoothStep(0, 0.7, FMath::Abs(RotationRate))*FMath::Sign(RotationRate)/2;
	
	if (Gait == EGait::WALKING)
		LeanBlend.Alpha = 0.0f;
	if (Gait == EGait::RUNNING)
		LeanBlend.Alpha = 1.0f;
	if (Gait == EGait::SPRINTING)
		LeanBlend.Alpha = 1.0f;

	//update WalkRunBlend
	if (Gait == EGait::WALKING)
		WalkRunBlend = 0.0f;
	else
		WalkRunBlend = 1.0f;
}