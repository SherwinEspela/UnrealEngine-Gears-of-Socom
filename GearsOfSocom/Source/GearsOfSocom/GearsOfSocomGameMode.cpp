// Copyright Epic Games, Inc. All Rights Reserved.

#include "GearsOfSocomGameMode.h"
#include "GearsOfSocomCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGearsOfSocomGameMode::AGearsOfSocomGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
