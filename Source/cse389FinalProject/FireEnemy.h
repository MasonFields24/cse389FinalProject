// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "FireEnemy.generated.h"

/**
 *
 */
UCLASS()
class CSE389FINALPROJECT_API AFireEnemy : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFireEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	bool bIsDead;
	bool bDetectsPlayer;
	bool bExplode;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	bool GetIsDead();
	UFUNCTION(BlueprintCallable)
	void SetIsDead(bool b);
	UFUNCTION(BlueprintCallable)
	bool GetDetectsPlayer();
	UFUNCTION(BlueprintCallable)
	void SetDetectsPlayer(bool b);
	UFUNCTION(BlueprintCallable)
	bool GetExplode();
	UFUNCTION(BlueprintCallable)
	void SetExplode(bool b);
};
