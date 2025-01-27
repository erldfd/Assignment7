// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HandmadeCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class ASSIGNMENT7_API AHandmadeCharacter : public APawn
{
	GENERATED_BODY()

public:
	AHandmadeCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

protected:

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	int MoveSpeed = 10;
};
