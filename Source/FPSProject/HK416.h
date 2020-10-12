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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
