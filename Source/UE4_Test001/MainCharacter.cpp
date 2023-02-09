// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "MainCharacterWidget.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.0f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	PlayerUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("PLAYERUI"));
	PlayerUI->SetupAttachment(GetCapsuleComponent());

	PlayerUI->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/Blueprints/CPPBlueprints/WBP_MainCharacter.WBP_MainCharacter_C'"));
	if (UW.Succeeded())
	{
		PlayerUI->SetWidgetClass(UW.Class);
	}

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMainCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMainCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::LookUp);
}

//void AMainCharacter::PostInitializeComponents()
//{
//	PlayerUI->InitWidget();
//}

void AMainCharacter::UpDown(float Value)
{
	if (Value == 0.f)
		return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

