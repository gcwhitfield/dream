// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class DREAM_API AInteractable : public AActor
{
	GENERATED_BODY()
	

private:
	// The icon to show on the screen when the player looks at this object.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UTexture2D* icon;

public:	
	// Sets default values for this actor's properties
	AInteractable();

};
