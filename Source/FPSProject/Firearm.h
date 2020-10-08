// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Firearm.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FAttachment : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
		USkeletalMeshComponent* mesh;
	UPROPERTY()
		UMaterial* material;
	UPROPERTY()
		int MatIndex;
};

UCLASS()
class FPSPROJECT_API AFirearm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirearm();

public:
	USkeletalMeshComponent* root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

