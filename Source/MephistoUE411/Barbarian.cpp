// Fill out your copyright notice in the Description page of Project Settings.

#include "MephistoUE411.h"
#include "Barbarian.h"
#include "Gold.h"


// Sets default values
ABarbarian::ABarbarian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	SetActorEnableCollision(true);

	static ConstructorHelpers::FObjectFinder<USoundBase> DeathAudio(TEXT("/Game/TopDownCPP/Audio/Death.Death"));
	DeathSound = DeathAudio.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> HurtAudio(TEXT("/Game/TopDownCPP/Audio/Hurt.Hurt"));
	HurtSound = HurtAudio.Object;
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

float ABarbarian::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health <= 0.f)
		{
			UWorld* const World = GetWorld();
			World->SpawnActor<AGold>(GetActorLocation(), GetActorRotation());
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
			SetLifeSpan(0.001f);
		}
		else {
			UGameplayStatics::PlaySoundAtLocation(this, HurtSound, GetActorLocation());
		}
	}

	return ActualDamage;
}

