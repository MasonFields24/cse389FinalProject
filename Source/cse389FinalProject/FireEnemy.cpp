// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEnemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AFireEnemy::AFireEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsDead = false;
	bDetectsPlayer = false;
}

void AFireEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AFireEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AFireEnemy::GetIsDead()
{
	return bIsDead;
}

void AFireEnemy::SetIsDead(bool b)
{
	bIsDead = b;
}

bool AFireEnemy::GetDetectsPlayer()
{
	return bDetectsPlayer;
}

void AFireEnemy::SetDetectsPlayer(bool b)
{
	bDetectsPlayer = b;
}

bool AFireEnemy::GetExplode()
{
	return bExplode;
}

void AFireEnemy::SetExplode(bool b)
{
	bExplode = b;
}

