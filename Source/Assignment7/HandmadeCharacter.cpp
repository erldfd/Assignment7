#include "HandmadeCharacter.h"

#include "MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AHandmadeCharacter::AHandmadeCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	ensure(CapsuleComp);

	SetRootComponent(CapsuleComp);

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	ensure(MeshComp);

	MeshComp->SetupAttachment(CapsuleComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprimgArm"));
	ensure(SpringArm);

	SpringArm->SetupAttachment(CapsuleComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AHandmadeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandmadeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHandmadeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AHandmadeCharacter::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AHandmadeCharacter::Look
				);
			}
		}
	}
}

void AHandmadeCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveInput = Value.Get<FVector2D>();
	MoveInput.Normalize();
	MoveInput *= MoveSpeed;

	AddActorLocalOffset(FVector(MoveInput.X, MoveInput.Y, 0), true);
}

void AHandmadeCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	AddActorLocalRotation(FRotator(0, LookInput.Y, 0));

	FRotator CharacterRotation = GetActorRotation();

	SpringArm->AddLocalRotation(FRotator(LookInput.X, 0, 0));
	SpringArm->SetWorldRotation(FRotator(SpringArm->GetComponentRotation().Pitch, CharacterRotation.Yaw, CharacterRotation.Roll));
}

