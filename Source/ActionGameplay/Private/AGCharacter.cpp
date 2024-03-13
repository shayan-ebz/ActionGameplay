// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AAGCharacter::AAGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true; // spring arm gets the input from the mouse 

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// rotate the character towards the movement [press w to run forward and then press d to turn the character to the right side running]
	GetCharacterMovement()->bOrientRotationToMovement = true; 

	// character is not turning (facing) based on the mouse movement (character can face towards camera)
	bUseControllerRotationYaw = false; 
}

// Called when the game starts or when spawned
void AAGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAGCharacter::MoveForward(float Value)
{
	// move the character in the direction of the control rotation (the direction of the camera)
	FRotator ControlRotation = GetControlRotation();
	// only interested in the yaw rotation value of the mouse for the movement so pitch and roll = 0;
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	// if we pass forward vector of the character it would go to the direction where the character is facing (and not forward) 
	AddMovementInput(ControlRotation.Vector() , Value);
}

void AAGCharacter::MoveRight(float Value)
{
	// move the character in the direction of the control rotation (the direction of the camera)
	FRotator ControlRotation = GetControlRotation();
	// only interested in the yaw rotation value of the mouse for the movement so pitch and roll = 0;
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	// calculate the right vector of the mouse input rotation (the right vector for the camera)
	FVector ControllerRightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	// if we pass the GetActorRightVector(), the character's right vector will be rotating with the character, resulting in 
	// circular rotation. pass that vector and test it if you don't remember what happens in the future.
	AddMovementInput(ControllerRightVector, Value);
}

// Called every frame
void AAGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAGCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

