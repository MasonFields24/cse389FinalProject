// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ANinja::ANinja()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ANinja::BeginPlay()
{
	Super::BeginPlay();
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
	PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &ANinja::Move);
}

//void ANinja::Move(const FInputActionValue& Value)
//{
//	if (Controller != nullptr) {
//		// Get location and rotation data
//		const FVector2D MoveValue = Value.Get<FVector2D>();
//		FVector Location = GetActorLocation();
//		UE_LOG(LogTemp, Warning, TEXT("Location: %f"), Location.X);
//
//		// if impacting the move forawrd key, move the ship in the forward direction of where it's facing
//		if (MoveValue.X != 0.0f) {
//			UE_LOG(LogTemp, Warning, TEXT("Should move"));
//			Location.X += MoveValue.X * 5;
//			SetActorLocation(Location);
//			/*Location += GetActorForwardVector() * MoveValue.X * 5;
//			SetActorLocation(Location);*/
//		}
//	}
//}

void ANinja::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		if (MoveValue.X != 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding movement input: %f"), MoveValue.X);
			AddMovementInput(FVector::RightVector, MoveValue.X); // For 2D movement along X-axis
		}
	}
}

