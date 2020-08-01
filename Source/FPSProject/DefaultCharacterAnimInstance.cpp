// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacterAnimInstance.h"

UDefaultCharacterAnimInstance::UDefaultCharacterAnimInstance()
{
	walkRun = 1.0f;
	stride = 0.0f;

	Gait = EGait::RUNNING;
	MovementDirection = EMovementDirection::FORWARD;

}

void UDefaultCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//set speed
	AActor* OwningActor = GetOwningActor();
	if (OwningActor != nullptr)
	{
		stride = OwningActor->GetVelocity().Size()/600;
	}

	if (Rotation <= -45.0f)
		MovementDirection = EMovementDirection::FORWARD;
	else if (Rotation <= -135.0f)
		MovementDirection = EMovementDirection::LEFT;
	else if (Rotation >= 45.0f)
		MovementDirection = EMovementDirection::RIGHT;
	else if (Rotation >= 0.0f)
		MovementDirection = EMovementDirection::FORWARD;
	else
		MovementDirection = EMovementDirection::BACKWARD;
}