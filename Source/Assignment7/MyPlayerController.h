// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class ASSIGNMENT7_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMyPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

public: // Drone

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneInput")
	UInputMappingContext* DroneInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneInput")
	UInputAction* DroneMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneInput")
	UInputAction* DroneRotatingAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneInput")
	UInputAction* DroneRollingAction;

protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* PawnToPossess) override;
};
