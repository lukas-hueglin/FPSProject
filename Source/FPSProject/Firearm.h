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

};

USTRUCT(BlueprintType, Blueprintable)
struct FAttachment : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* Material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName SocketName;

};

USTRUCT(BlueprintType)
struct FAttachmentComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment AssistPlunger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment Bolt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment BoltCatch;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment BufferSystem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment ChargingHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment EjectionCover;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment Gasblock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment Rail;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment Barrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment LowerReceiver;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment MagazineCatch;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment ModeSwitch;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment PistolGrip;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment Stock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment Trigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FAttachment UpperReceiver;
};

UCLASS()
class FPSPROJECT_API AFirearm : public AActor
{
	GENERATED_BODY()
	
public:
	// root skeletalmesh
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* RootMesh;

	// Attachments
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		FAttachmentComponent AttachmentComponent;

public:	
	// Sets default values for this actor's properties
	AFirearm();

public:
	// Array of all Layouts
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Layouts)
		TArray<UDataTable*> Layouts;
	// the Active Layout data table
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Layouts)
		UDataTable* ActiveLayout;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to update an attachment
	void UpdateAttachment(FAttachment Attachment);

};

