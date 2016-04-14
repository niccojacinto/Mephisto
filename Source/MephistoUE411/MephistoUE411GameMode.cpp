// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MephistoUE411.h"
#include "MephistoUE411GameMode.h"
#include "MephistoUE411PlayerController.h"
#include "MephistoUE411Character.h"

AMephistoUE411GameMode::AMephistoUE411GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMephistoUE411PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}