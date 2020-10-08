// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firearm.h"
#include "HK416.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AHK416 : public AFirearm
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHK416();

public:
	//All attachment sockets
	UPROPERTY()
		FAttachment AssistPlunger;
	UPROPERTY()
		FAttachment Barrel;
	UPROPERTY()
		FAttachment Bolt;
	UPROPERTY()
		FAttachment BoltCatch;
	UPROPERTY()
		FAttachment BufferSystem;
	UPROPERTY()
		FAttachment ChargingHandle;
	UPROPERTY()
		FAttachment EjectionCover;
	UPROPERTY()
		FAttachment Gasblock;
	UPROPERTY()
		FAttachment LowerReceiver;
	UPROPERTY()
		FAttachment MagazineCatch;
	UPROPERTY()
		FAttachment ModeSwitch;
	UPROPERTY()
		FAttachment PistolGrip;
	UPROPERTY()
		FAttachment Rail;
	UPROPERTY()
		FAttachment Stock;
	UPROPERTY()
		FAttachment Trigger;
	UPROPERTY()
		FAttachment UpperReceiver;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
