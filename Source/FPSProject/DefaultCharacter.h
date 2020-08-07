// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

class UDefaultCharacterAnimInstance;

UCLASS()
class FPSPROJECT_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

		//Pawn mesh
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* CharacterMesh;

		//First person camera
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UCameraComponent* FirstPersonCamera;

public:
	// Sets default values for this character's properties
	ADefaultCharacter();
public:
	UDefaultCharacterAnimInstance* AnimInstance;

	bool bPressedWalk;
	bool bPressedSprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	//Called to bind sprint state
	UFUNCTION()
		void StartSprint();
	UFUNCTION()
		void StopSprint();
};
