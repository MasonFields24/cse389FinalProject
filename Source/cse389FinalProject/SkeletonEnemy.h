// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "SkeletonEnemy.generated.h"

/**
 *
 */
UCLASS()
class CSE389FINALPROJECT_API ASkeletonEnemy : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkeletonEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	bool bIsDead;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	bool GetIsDead();
	UFUNCTION(BlueprintCallable)
	void SetIsDead(bool b);
};
