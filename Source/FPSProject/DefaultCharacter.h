// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Firearm.h"
#include "HK416.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

class UDefaultCharacterAnimInstance;

UENUM(BlueprintType)
enum class EActiveEquipmentSlot : uint8
{
	NONE		UMETA(DisplayName = "None"),
	PRIMARY		UMETA(DisplayName = "Primary"),
};

USTRUCT(BlueprintType)
struct FEquipment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AHK416* Primary;
};

UCLASS()
class FPSPROJECT_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

		//Pawn mesh
		UPROPERTY(EditAnywhere, Category = Mesh)
			class USkeletalMeshComponent* CharacterMesh;

		//First person camera
		UPROPERTY(EditAnywhere, Category = Camera)
			class UCameraComponent* FirstPersonCamera;

public:
	// Sets default values for this character's properties
	ADefaultCharacter();
public:
	UDefaultCharacterAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAiming;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPressedWalk;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPressedSprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bCanSprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EActiveEquipmentSlot ActiveEquipmentSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FEquipment Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawning)
		TSubclassOf<class AHK416> HK416Class;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SecondaryAction
	UFUNCTION()
		void StartSecondaryAction();
	UFUNCTION()
		void StopSecondaryAction();

	//Called to bind movement input
	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);

	//Called to bind jump input
	UFUNCTION()
		void StartJump();
	UFUNCTION()
		void StopJump();

	//Called to bind walk state
	UFUNCTION()
		void ToggleWalk();
	
	// Called to cycle trough all weapons
	UFUNCTION()
		void CycleEquipment();

	//Called to bind sprint state
	UFUNCTION()
		void StartSprint();
	UFUNCTION()
		void StopSprint();
};