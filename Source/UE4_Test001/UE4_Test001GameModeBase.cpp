// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4_Test001GameModeBase.h"
#include "MainCharacter.h"

AUE4_Test001GameModeBase::AUE4_Test001GameModeBase()
{
	/*static ConstructorHelpers::FClassFinder<AMainCharacter> BP_Char(TEXT("Blueprint'/Game/Blueprints/CPPBlueprints/BP_MainCharacter.BP_MainCharacter_C"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}*/
	DefaultPawnClass = AMainCharacter::StaticClass();
}
