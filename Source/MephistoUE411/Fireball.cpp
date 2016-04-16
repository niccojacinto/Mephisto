// Fill out your copyright notice in the Description page of Project Settings.

#include "MephistoUE411.h"
#include "Fireball.h"
#include "Barbarian.h"


// Sets default values
AFireball::AFireball()
{

	duration = 3.0f;
	speed = 20.0f;


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(10.0f);

	// Sphere
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Visual"));
	SphereVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
		SphereVisual->SetWorldScale3D(FVector(0.2f));
	}

	// Molten Rock Material -- Using Grime at the moment
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/StarterContent/Materials/M_Concrete_Grime.M_Concrete_Grime"));
	if (Material.Succeeded()) {
		UMaterialInstance* MoltenRock = (UMaterialInstance*)Material.Object;
		// UMaterialInstanceDynamic* MI = UMaterialInstanceDynamic::Create(SphereVisual->GetMaterial(0), MoltenRock);

		SphereVisual->SetMaterial(0, Material.Object);
	}


	// Fire Particles
	UParticleSystemComponent* OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->AttachTo(RootComponent);
	OurParticleSystem->bAutoActivate =  true;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded()) {
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}


	deathParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeathParticles"));
	deathParticle->AttachTo(RootComponent);
	deathParticle->bAutoActivate = false;
	deathParticle->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DeathAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DeathAsset.Succeeded()) {
		deathParticle->SetTemplate(DeathAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TopDownCPP/Audio/FireballHit.FireballHit"));
	HitSound = FireAudio.Object;


	SetActorEnableCollision(true);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFireball::OnHit);
	// SphereVisual->OnComponentBeginOverlap.AddDynamic(this, &AFireball::OnHit);


}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();
;
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

void AFireball::OnHit(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != NULL && OtherActor != this && OtherComp != NULL) {

		if (OtherActor->IsA(ABarbarian::StaticClass())) {
			deathParticle->Activate(true);
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

	}
}

