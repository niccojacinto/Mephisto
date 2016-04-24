// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemyPortal.generated.h"



UCLASS(Blueprintable)
class MEPHISTOUE411_API AEnemyPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Settings for the Spawner
	// Object To Spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
		uint8 maxSpawned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
		float spawnDelayInSeconds = 0;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
		TSubclassOf<class ABarbarian> enemy;

	float spawnTimer;
	uint8 numSpawned;


	// Sets default values for this actor's properties
	AEnemyPortal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Spawn();
	
};
