#include "MyDrone.h"

#include "MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMyDrone::AMyDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	ensure(BoxComp);

	SetRootComponent(BoxComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	ensure(SpringArm);

	SpringArm->SetupAttachment(BoxComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	ensure(CameraComp);

	CameraComp->SetupAttachment(SpringArm);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ensure(MeshComp);

	MeshComp->SetupAttachment(BoxComp);
}

void AMyDrone::BeginPlay()
{
	Super::BeginPlay();
}

void AMyDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float RecoverRate = 1.0f;

	if (FMath::IsNearlyZero(CurrentMoveInput.X))
	{
		CurrentVelocity.X -= CurrentVelocity.X * RecoverRate * DeltaTime;

		if (FMath::IsNearlyZero(CurrentVelocity.X))
		{
			CurrentVelocity.X = 0;
		}

		CurrentMeshRotation.Pitch += (DefaultMeshRotation.Pitch - CurrentMeshRotation.Pitch) * DeltaTime;

		if (FMath::IsNearlyZero(CurrentMeshRotation.Pitch - DefaultMeshRotation.Pitch))
		{
			CurrentMeshRotation.Pitch = DefaultMeshRotation.Pitch;
		}
	}
	
	if (FMath::IsNearlyZero(CurrentMoveInput.Y))
	{
		CurrentVelocity.Y -= CurrentVelocity.Y * RecoverRate * DeltaTime;

		if (FMath::IsNearlyZero(CurrentVelocity.Y))
		{
			CurrentVelocity.Y = 0;
		}

		CurrentMeshRotation.Roll += (DefaultMeshRotation.Roll - CurrentMeshRotation.Roll) * DeltaTime;

		if (FMath::IsNearlyZero(CurrentMeshRotation.Roll - DefaultMeshRotation.Roll))
		{
			CurrentMeshRotation.Roll = DefaultMeshRotation.Roll;
		}
	}
	
	if (FMath::IsNearlyZero(CurrentMoveInput.Z))
	{
		CurrentVelocity.Z -= CurrentVelocity.Z * RecoverRate * DeltaTime;

		if (FMath::IsNearlyZero(CurrentVelocity.Z))
		{
			CurrentVelocity.Z = 0;
		}
	}

	AddActorLocalOffset(CurrentVelocity * DeltaTime, true);
	MeshComp->SetRelativeRotation(CurrentMeshRotation.Quaternion());

	//SetActorRotation(FMath::Lerp(GetActorRotation(), TargetRotation, 0.1f));
	//SetActorRotation(TargetRotation);
	/*if ((GetActorRotation() - TargetRotation).IsNearlyZero())
	{
		SetActorRotation(TargetRotation);
	}*/
}

void AMyDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->DroneMoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->DroneMoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyDrone::Move
				);

				EnhancedInput->BindAction(
					PlayerController->DroneMoveAction,
					ETriggerEvent::Completed,
					this,
					&AMyDrone::CancelMove
				);
			}

			if (PlayerController->DroneRotatingAction)
			{
				EnhancedInput->BindAction(
					PlayerController->DroneRotatingAction,
					ETriggerEvent::Triggered,
					this,
					&AMyDrone::Rotating
				);
			}

			if (PlayerController->DroneRollingAction)
			{
				EnhancedInput->BindAction(
					PlayerController->DroneRollingAction,
					ETriggerEvent::Triggered,
					this,
					&AMyDrone::Rolling
				);
			}
		}
	}
}

void AMyDrone::Move(const FInputActionValue& Value)
{
	FVector MoveInput = Value.Get<FVector>();

	CurrentVelocity += MoveInput;
	CurrentMoveInput = MoveInput;
	if (CurrentVelocity.Size() > MaxSpeed)
	{
		CurrentVelocity.Normalize();
		CurrentVelocity *= MaxSpeed;
	}

	bIsMoving = true;

	FVector& Delta = MoveInput;
	Delta.Normalize();

	FRotator DeltaRot(-Delta.X, 0, Delta.Y);
	CurrentMeshRotation += DeltaRot;
	CurrentMeshRotation.Pitch = FMath::Clamp(CurrentMeshRotation.Pitch, DefaultMeshRotation.Pitch - MaxMeshRotationDelta, DefaultMeshRotation.Pitch + MaxMeshRotationDelta);
	CurrentMeshRotation.Yaw = FMath::Clamp(CurrentMeshRotation.Yaw, DefaultMeshRotation.Yaw - MaxMeshRotationDelta, DefaultMeshRotation.Yaw + MaxMeshRotationDelta);
	CurrentMeshRotation.Roll = FMath::Clamp(CurrentMeshRotation.Roll, DefaultMeshRotation.Roll - MaxMeshRotationDelta, DefaultMeshRotation.Roll + MaxMeshRotationDelta);
}

void AMyDrone::CancelMove(const FInputActionValue& Value)
{
	bIsMoving = false;
	CurrentMoveInput = FVector::ZeroVector;
}

void AMyDrone::Rotating(const FInputActionValue& Value)
{
	FVector2D RotatingInput = Value.Get<FVector2D>();

	AddControllerYawInput(RotatingInput.X);
	AddControllerPitchInput(RotatingInput.Y);

	//TargetRotation = Controller->AActor::GetActorRotation();
}

void AMyDrone::Rolling(const FInputActionValue& Value)
{
	float Rolling = Value.Get<float>();

	UE_LOG(LogTemp, Error, TEXT("Drone Rolling Input : %f"), Rolling);
}

