// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ADefaultCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADefaultCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADefaultCharacter::StopJump);
}

void ADefaultCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Value);
	}
}

void ADefaultCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = GetActorRightVector();
		AddMovementInput(Direction, Value);
	}
}

void ADefaultCharacter::StartJump()
{
	bPressedJump = true;
}

void ADefaultCharacter::StopJump()
{
	bPressedJump = false;
}

