// Fill out your copyright notice in the Description page of Project Settings.

#include "MephistoUE411.h"
#include "Fireball.h"


// Sets default values
AFireball::AFireball()
{
	duration = 3.0f;
	speed = 20.0f;


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Collider
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	// SphereComponent->AttachTo(RootComponent);
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);

	UParticleSystem* FlameParticle = CreateDefaultSubobject<UParticleSystem>(TEXT("Particle System"));
	// FlameParticle->AttachTo(RootComponent);

	// Placeholder
	
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Visual"));
	SphereVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SphereVisual->SetWorldScale3D(FVector(0.2f));
	}
	

	// Create a particle system that we can activate or deactivate
	UParticleSystemComponent* OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->AttachTo(RootComponent);
	OurParticleSystem->bAutoActivate =  true;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireball::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	duration -= DeltaTime;
	if (duration <= 0) Destroy(true);

	FVector newPos = GetActorLocation() + GetActorForwardVector() * speed;
	SetActorLocation(newPos);
}

