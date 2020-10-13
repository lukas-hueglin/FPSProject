// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view(when controlling this pawn)
	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(GetCapsuleComponent());
	CharacterMesh->bCastDynamicShadow = true;
	CharacterMesh->CastShadow = true;
	CharacterMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	CharacterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -89.0f));

	// Create a CameraComponent	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(CharacterMesh, FName("FP_Camera"));
	FirstPersonCamera->SetRelativeLocation(FVector(10.0f, 0.0f, 83.0f)); // Position the camera 10.0f, 0.0f, 83.0f
	FirstPersonCamera->bUsePawnControlRotation = true;

	//Initialize bools
	bPressedSprint = false;
	bPressedWalk = false;
	bAiming = false;
	bCanSprint = true;

	//Initialize Enums
	Equipment = EEquipment::NONE;

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

	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &ADefaultCharacter::StartSecondaryAction);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Released, this, &ADefaultCharacter::StopSecondaryAction);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ADefaultCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADefaultCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADefaultCharacter::StopJump);

	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &ADefaultCharacter::ToggleWalk);

	PlayerInputComponent->BindAction("CycleEquipment", IE_Pressed, this, &ADefaultCharacter::CycleEquipment);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ADefaultCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ADefaultCharacter::StopSprint);
}

void ADefaultCharacter::StartSecondaryAction()
{
	bAiming = true;
}

void ADefaultCharacter::StopSecondaryAction()
{
	bAiming = false;
}

void ADefaultCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Value);

		if (Value > 0.0f)
			bCanSprint = true;
		else
			bCanSprint = false;
	}
}

void ADefaultCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = GetActorRightVector();
		AddMovementInput(Direction, Value);
		bCanSprint = false;
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

void ADefaultCharacter::ToggleWalk()
{
	bPressedWalk = !bPressedWalk;
}

void ADefaultCharacter::CycleEquipment()
{
	//Equipment = EEquipment((uint8)Equipment + 1U);
	if (Equipment == EEquipment::NONE)
		Equipment = EEquipment::PRIMARY;
	else
		Equipment = EEquipment::NONE;
}

void ADefaultCharacter::StartSprint()
{
		bPressedSprint = true;
		bPressedWalk = false;
}

void ADefaultCharacter::StopSprint()
{
	bPressedSprint = false;
}

