// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperTileMapComponent.h"
#include "SkeletonEnemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANinja::ANinja()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bCanTakeDamage = true;
	bIsDead = false;
	// 1.5 second iframes
	DamageCooldown = 1.5f;
}

void ANinja::BeginPlay()
{
	Super::BeginPlay();

	
	UBoxComponent* ClimbHitbox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("ClimbHitbox")));
	ClimbHitbox->OnComponentBeginOverlap.AddDynamic(this, &ANinja::OnClimbHitboxBeginOverlap);
	ClimbHitbox->OnComponentEndOverlap.AddDynamic(this, &ANinja::OnClimbHitboxEndOverlap);

	Hitbox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("Hitbox")));
	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ANinja::OnOverlapBegin);
}

void ANinja::ResetCanTakeDamage()
{
	bCanTakeDamage = true;
}

void ANinja::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANinja::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the play controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PEI->BindAction(InputWallClimb, ETriggerEvent::Triggered, this, &ANinja::WallClimb);
}

void ANinja::WallClimb(const FInputActionValue& Value)
{
	if (bCanClimb)
	{
		float ClimbDirection = Value.Get<float>();
		FVector CurrentLocation = GetActorLocation();
		float ClimbSpeed = 150.0f;

		// Calculate the new location based on input direction
		FVector NewLocation = CurrentLocation + FVector(0.0f, 0.0f, ClimbDirection * ClimbSpeed * GetWorld()->DeltaTimeSeconds);

		// Update the actor's location
		SetActorLocation(NewLocation);
	}
}

void ANinja::OnClimbHitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the actor has a UPaperTileMapComponent
	UPaperTileMapComponent* TileMapComponent = OtherActor->FindComponentByClass<UPaperTileMapComponent>();
	if (TileMapComponent)
	{
		bCanClimb = true;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void ANinja::OnClimbHitboxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the actor has a UPaperTileMapComponent
	UPaperTileMapComponent* TileMapComponent = OtherActor->FindComponentByClass<UPaperTileMapComponent>();
	if (TileMapComponent)
	{
		bCanClimb = false;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

int ANinja::GetHealth() {
	return Health;
}

void ANinja::SetHealth(int NewHealth) {
	Health = NewHealth;
}

int ANinja::GetScore() {
	return Score;
}

void ANinja::SetScore(int NewScore) {
	Score = NewScore;
}

void ANinja::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If in iframes, ignore
	if (!bCanTakeDamage) {
		return;
	}
	// Component
	FString ComponentName = OtherComp->GetName();
	// Skeleton body
	ASkeletonEnemy* Skeleton = Cast<ASkeletonEnemy>(OtherActor);
	
	// Deal damage if the cast succeeded or we hit the skeleton's PlayerDetector
	if (Skeleton || ComponentName == "PlayerDetector")
	{
		if (!Skeleton->GetIsDead()) {
			Health -= 1;
			bCanTakeDamage = false;
			GetWorld()->GetTimerManager().SetTimer(
				DamageCooldownTimerHandle, this, &ANinja::ResetCanTakeDamage, DamageCooldown, false);
		}
	}

	CheckIsDead();
}

void ANinja::CheckIsDead() {
	if (Health <= 0) {
		bIsDead = true;
	}
}

bool ANinja::GetIsDead()
{
	return bIsDead;
}
