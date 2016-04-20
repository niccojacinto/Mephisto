// Fill out your copyright notice in the Description page of Project Settings.

#include "MephistoUE411.h"
#include "MephistoUE411Character.h"
#include "Gold.h"


// Sets default values
AGold::AGold()
{
	rotspeed = 100.0f;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);

	// Coin Shape a.k.a Cylinder
	CoinVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Visual"));
	CoinVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CoinVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (CoinVisualAsset.Succeeded())
	{
		CoinVisual->SetStaticMesh(CoinVisualAsset.Object);
		CoinVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
		CoinVisual->SetWorldScale3D(FVector(0.3f,0.3f,0.1f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (Material.Succeeded()) {
		CoinVisual->SetMaterial(0, Material.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> PickupAudio(TEXT("/Game/TopDownCPP/Audio/Coin.Coin"));
	PickupSound = PickupAudio.Object;

	SetActorEnableCollision(true);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGold::OnHit);
}

// Called when the game starts or when spawned
void AGold::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGold::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AddActorLocalRotation(FRotator(rotspeed * DeltaTime, 0, 0));
}

void AGold::OnHit(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != NULL && OtherActor != this && OtherComp != NULL) {

		if (OtherActor->IsA(AMephistoUE411Character::StaticClass())) {
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
			Destroy(true);
		}
	}
}

