// Fill out your copyright notice in the Description page of Project Settings.

#include "MephistoUE411.h"
#include "EnemyPortal.h"
#include "Barbarian.h" // Change later on to an enemyclass

// Sets default values
AEnemyPortal::AEnemyPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spawnTimer = 0;
	numSpawned = 0;
}

// Called when the game starts or when spawned
void AEnemyPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPortal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	spawnTimer -= DeltaTime;
	if (spawnTimer < 0) {
		Spawn();
	}
}

void AEnemyPortal::Spawn() {
	if (numSpawned >= maxSpawned) { return;  }
	UWorld* const World = GetWorld();
	ABarbarian* myEnemy = World->SpawnActor<ABarbarian>(enemy, GetActorLocation(), GetActorRotation());
	spawnTimer = spawnDelayInSeconds;
	numSpawned++;
}

