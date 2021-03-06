// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MephistoUE411.h"
#include "MephistoUE411Character.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Fireball.h"
#include "MyAnimInstance.h"

AMephistoUE411Character::AMephistoUE411Character()
{
	FHealth = FMana = 1.0f;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMephistoUE411Character::Tick(float DeltaSeconds)
{
	if (FMana < 1.0f)
	{
		FMana += 0.001f;
	}
	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);

			if (!GetMesh()) return;
			UMyAnimInstance* Animation = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
			if (!Animation) return;
			Animation->Attacking = false;
		}
	}
}

void AMephistoUE411Character::CastFireball(const FVector TargetLocation) {
	if (FMana > 0.2f)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Casting Fireball"));

		// Spawn projectile at an offset from this pawn
		FVector Direction = TargetLocation - GetActorLocation();
		FRotator NewRot = Direction.Rotation();
		NewRot.Pitch = GetActorRotation().Pitch;
		// NewRot.Yaw = FRotator::ClampAxis(NewRot.Yaw);
		SetActorRotation(NewRot);

		const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100;

		UWorld* const World = GetWorld();
		// spawn the projectile

		// World->SpawnActor<AFireball>(SpawnLocation, Direction.Rotation()); //Direction To Cursor
		World->SpawnActor<AFireball>(SpawnLocation, GetActorRotation()); // Direction To Player Rotation

		FMana -= 0.2f;

		if (!GetMesh()) return;
		UMyAnimInstance* Animation = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
		if (!Animation) return;
		Animation->Attacking = true;
	}
}
