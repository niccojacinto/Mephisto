// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Barbarian.generated.h"

UCLASS()
class MEPHISTOUE411_API ABarbarian : public ACharacter
{
	GENERATED_BODY()

public:

	USoundBase* DeathSound;
	USoundBase* HurtSound;

	float Health;
	// Sets default values for this character's properties
	ABarbarian();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Set size for player capsule
	//	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
