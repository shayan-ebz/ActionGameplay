// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AGCharacter.generated.h"


/* Forward Declarations */
class USpringArmComponent;
class UCameraComponent;





UCLASS() 
class ACTIONGAMEPLAY_API AAGCharacter : public ACharacter
{
	GENERATED_BODY()




/* ///////////////////////////////////			Member Functions				//////////////////////////////////// */
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	// Called via input binding component when the forward movement key is pressed(W,S)
	void MoveForward(float Value);
	
	// Called via input binding component when the side movement key is pressed(A,D)
	void MoveRight(float Value);

private:


/* ///////////////////////////////////			Data Members				//////////////////////////////////// */
public:

	// Sets default values for this character's properties
	AAGCharacter();


protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

private:

};
