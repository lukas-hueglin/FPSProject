// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Firearm.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FAllAttachments : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterial* Material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName SocketName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int maxMatIndex;
};

USTRUCT(BlueprintType, Blueprintable)
struct FAttachment : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterial* Material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		signed int matIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float dirtAmount;
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

