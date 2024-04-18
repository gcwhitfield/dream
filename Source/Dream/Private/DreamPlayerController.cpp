// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ADreamPlayerController::BeginPlay() {
	Super::BeginPlay();
	// Get the enhances input subsystem.
	UE_LOG(LogTemp, Warning, TEXT("log1 beginplay"));
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		// Add the mapping context to enable controls.
		Subsystem->AddMappingContext(InputMappingContext, 0);
		UE_LOG(LogTemp, Warning, TEXT("Enhanced subsystem added to ULocalPlayer."));
	}
}