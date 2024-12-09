// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperTileMapComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANinja::ANinja()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ANinja::BeginPlay()
{
	Super::BeginPlay();

	
	UBoxComponent* ClimbHitbox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("ClimbHitbox")));
	ClimbHitbox->OnComponentBeginOverlap.AddDynamic(this, &ANinja::OnClimbHitboxBeginOverlap);
	ClimbHitbox->OnComponentEndOverlap.AddDynamic(this, &ANinja::OnClimbHitboxEndOverlap);

	UBoxComponent* FootHitbox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("FootHitbox")));
	FootHitbox->OnComponentBeginOverlap.AddDynamic(this, &ANinja::OnFootHitboxBeginOverlap);
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
		float ClimbDirection = Value.Get<float>(); // Get input direction (-1 for down, +1 for up)
		FVector CurrentLocation = GetActorLocation(); // Get the current location of the character
		float ClimbSpeed = 200.0f; // Adjust for desired climbing speed

		// Calculate the new location based on input direction
		FVector NewLocation = CurrentLocation + FVector(0.0f, 0.0f, ClimbDirection * ClimbSpeed * GetWorld()->DeltaTimeSeconds);

		// Update the actor's location
		SetActorLocation(NewLocation);

		if (ClimbDirection > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Climbing Up!"));
		}
		else if (ClimbDirection < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Climbing Down!"));
		}
	}
}

void ANinja::OnClimbHitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the actor has a UPaperTileMapComponent
	UPaperTileMapComponent* TileMapComponent = OtherActor->FindComponentByClass<UPaperTileMapComponent>();
	if (TileMapComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Climbable tileset detected!"));
		bCanClimb = true;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying); // Enable Flying mode
		//GetCharacterMovement()->GravityScale = 0.0f; // Disable gravity
	}
}

void ANinja::OnClimbHitboxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the actor has a UPaperTileMapComponent
	UPaperTileMapComponent* TileMapComponent = OtherActor->FindComponentByClass<UPaperTileMapComponent>();
	if (TileMapComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Left tileset!"));
		bCanClimb = false;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking); // Enable Flying mode
		//GetCharacterMovement()->GravityScale = 1.0f; // Disable gravity
	}
}

void ANinja::OnFootHitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bCanClimb = false;
}