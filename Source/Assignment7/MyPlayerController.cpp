#include "MyPlayerController.h"

#include "HandmadeCharacter.h"
#include "MyDrone.h"

#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr),
	DroneInputMappingContext(nullptr),
	DroneMoveAction(nullptr),
	DroneRotatingAction(nullptr),
	DroneRollingAction(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (Subsystem == nullptr)
	{
		return;
	}

	if (Cast<AHandmadeCharacter>(PawnToPossess))
	{
		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	else
	{
		if (DroneInputMappingContext)
		{
			Subsystem->AddMappingContext(DroneInputMappingContext, 0);
		}
	}
}
