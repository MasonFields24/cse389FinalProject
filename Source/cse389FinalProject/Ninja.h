// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Ninja.generated.h"

/**
 *
 */
UCLASS()
class CSE389FINALPROJECT_API ANinja : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANinja();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputWallClimb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climbing")
	bool bCanClimb = false;
	int Health = 3;
	int Score = 0;
	bool bCanTakeDamage;
	bool bIsDead;
	float DamageCooldown;
	FTimerHandle DamageCooldownTimerHandle;

	void ResetCanTakeDamage();

	UBoxComponent* Hitbox;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void WallClimb(const FInputActionValue& Value);

	UFUNCTION()
	void OnClimbHitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnClimbHitboxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	int GetHealth();
	UFUNCTION(BlueprintCallable)
	int GetScore();
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void CheckIsDead();
	UFUNCTION(BlueprintCallable)
	bool GetIsDead();
};
