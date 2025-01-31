// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyDrone.generated.h"

struct FInputActionValue;

UCLASS()
class ASSIGNMENT7_API AMyDrone : public APawn
{
	GENERATED_BODY()

public:

	AMyDrone();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void CancelMove(const FInputActionValue& Value);
	void Rotating(const FInputActionValue& Value);
	void Rolling(const FInputActionValue& Value);

protected:

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "DroneSettings")
	float RPM = 10;

	float CurrentLift = 0;

	FVector CurrentVelocity = FVector::ZeroVector;
	FRotator CurrentMeshRotation = FRotator(0, 00, 0);
	FRotator DefaultMeshRotation = FRotator(0, 00, 0);
	float MaxMeshRotationDelta = 10.0f;
	FVector CurrentMoveInput = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "DroneSettings")
	float MaxSpeed = 300;

	bool bIsMoving = false;

	FRotator TargetRotation = FRotator::ZeroRotator;
};
