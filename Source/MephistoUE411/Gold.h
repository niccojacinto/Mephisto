// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Gold.generated.h"

UCLASS()
class MEPHISTOUE411_API AGold : public AActor
{
	GENERATED_BODY()
	
public:	
	USoundBase* PickupSound;

	float rotspeed;

	USphereComponent* SphereComponent;
	UStaticMeshComponent* CoinVisual;

	// Sets default values for this actor's properties
	AGold();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UFUNCTION()
		void OnHit(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
