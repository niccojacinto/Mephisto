// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MephistoUE411.h"
#include "MephistoUE411Character.h"
#include "MephistoUE411PlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "TimerManager.h"


AMephistoUE411PlayerController::AMephistoUE411PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	castRate = 1.0f;
	bCanCast = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TopDownCPP/Audio/FireballCast.FireballCast"));
	FireSound = FireAudio.Object;
}

void AMephistoUE411PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{

		if (bCastMode) {
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			CastFireball(Hit.ImpactPoint);
		}
		else {
			MoveToMouseCursor();
		}

	}


}

void AMephistoUE411PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMephistoUE411PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMephistoUE411PlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("ToggleCastMode", IE_Pressed, this, &AMephistoUE411PlayerController::ToggleCastMode);
	InputComponent->BindAction("ToggleCastMode", IE_Released, this, &AMephistoUE411PlayerController::ToggleCastMode);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMephistoUE411PlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMephistoUE411PlayerController::MoveToTouchLocation);
}

void AMephistoUE411PlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMephistoUE411PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMephistoUE411PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMephistoUE411PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMephistoUE411PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AMephistoUE411PlayerController::ToggleCastMode() {
	bCastMode = bCastMode ? false : true;
}

void AMephistoUE411PlayerController::CastFireball(const FVector Location) {

	if (bCanCast) {

		AMephistoUE411Character* const Pawn = Cast<AMephistoUE411Character>(GetPawn());

		if (Pawn) {
			// FVector2D ScreenSpaceLocation(Location);

			// FHitResult HitResult;
			// GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);

			Pawn->CastFireball(Location);

			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Pawn->GetActorLocation());

			bCanCast = false;
			UWorld* const World = GetWorld();
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMephistoUE411PlayerController::ShotTimerExpired, castRate);
		}
	}
}

void AMephistoUE411PlayerController::ShotTimerExpired() {
	bCanCast = true;
}