// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ADreamCharacter::ADreamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera component.
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ADreamCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Add the Input Mapping Context.
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(IC_Player, 0);
		}
	}
}

// Check to see if the player is looking at an interactable object.
UInteractableComponent* ADreamCharacter::IsLookingAtInteractable() const {
	// Do a raycast to see if the player is looking at the interactable.
	FHitResult hitResult;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	if (UWorld* world = GetWorld(); world != nullptr) {
		DrawDebugLine(
			world,
			FirstPersonCamera->GetComponentLocation(),
			FirstPersonCamera->GetComponentLocation() + (FirstPersonCamera->GetForwardVector() * InteractableRaycastDistance), 
			FColor::Red, 
			false);
		
		if (world->LineTraceSingleByChannel(
			hitResult,
			FirstPersonCamera->GetComponentLocation(),
			FirstPersonCamera->GetComponentLocation() + (FirstPersonCamera->GetForwardVector() * InteractableRaycastDistance),
			ECC_WorldStatic,
			queryParams)) {
			UE_LOG(LogTemp, Warning, TEXT("Hit"));
			AActor* hitActor = hitResult.GetActor();
			return hitActor->GetComponentByClass<UInteractableComponent>();
			return nullptr;
		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("Raycast failed :("));
		}
		
			
	}
	return nullptr;
}



// Called every frame
void ADreamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (UInteractableComponent* interactable = IsLookingAtInteractable(); interactable != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("looking at interactable"));
	}
}

// Called to bind functionality to input
void ADreamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving.
		EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &ADreamCharacter::Move);
		// Looking.
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ADreamCharacter::Look);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADreamCharacter::Move(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ADreamCharacter::Look(const FInputActionValue& Value) {
	FVector2D LookVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(-LookVector.Y);
	}
}

