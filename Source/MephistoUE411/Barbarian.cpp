// Fill out your copyright notice in the Description page of Project Settings.

#include "MephistoUE411.h"
#include "Barbarian.h"


// Sets default values
ABarbarian::ABarbarian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for player capsule
	// GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
}

// Called when the game starts or when spawned
void ABarbarian::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarbarian::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABarbarian::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

