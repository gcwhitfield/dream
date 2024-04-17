// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamCharacter.h"

// Sets default values
ADreamCharacter::ADreamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADreamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADreamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADreamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADreamCharacter::Move(const FInputActionValue& Value) {

}

void ADreamCharacter::Look(const FInputActionValue& Value) {
	
}

