// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Fireball.generated.h"

UCLASS()
class MEPHISTOUE411_API AFireball : public AActor
{
	GENERATED_BODY()
	
public:	

	float duration;
	float speed;

	USphereComponent* SphereComponent;
	UStaticMeshComponent* SphereVisual;

	USoundBase* HitSound;
	UParticleSystemComponent* deathParticle;

	// Sets default values for this actor's properties
	AFireball();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UFUNCTION()
		void OnHit(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	
	
};
