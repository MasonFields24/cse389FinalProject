// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonEnemy.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperTileMapComponent.h"
#include "Ninja.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASkeletonEnemy::ASkeletonEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsDead = false;
}

void ASkeletonEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ASkeletonEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASkeletonEnemy::GetIsDead()
{
	return bIsDead;
}

void ASkeletonEnemy::SetIsDead(bool b)
{
	bIsDead = b;
}

