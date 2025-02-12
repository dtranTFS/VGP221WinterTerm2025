// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!FPSCameraComponent) {
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	if (!FPSMesh) {
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		FPSMesh->SetupAttachment(FPSCameraComponent);
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;
	}

	GetMesh()->SetOwnerNoSee(true);

	UE_LOG(LogTemp, Warning, TEXT("Character constructor is called"));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRightCusIWantTo);

	// Look
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);

	// Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float value)
{
	// 1. Unreal method from tutorial
	// Find out which way is "forward" and record that the player wants to move that way.
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	// 2. Looking through documentation
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRightCusIWantTo(float value)
{
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	// Different methods of making the character jump through documentation
	bPressedJump = true;

	//Jump();
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (!ProjectileClass) return;

	// Init relevant infomration for where the projectile will be
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += 10.0f;

	// Start of spawning the projectile
	UWorld* World = GetWorld();
	if (!World)  return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// Unity Instantiate
	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (!Projectile) return;

	// Launch spawned projectile in the camera rotation
	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);

	Damage(10);
}

void AFPSCharacter::Damage(float damageAmt)
{
	Health -= damageAmt;
	float HealthPercent = Health / MaxHealth; // Value betwen 0.0 - 1.0

	// Updating UI
	// Method 1: Get Actor of class
	// AHUD* HUD = Cast<AHUD>(UGameplayStatics::GetActorOfClass(GetWorld(), AHUD::StaticClass()));
	// AFPSHUD* FPSHUD = Cast<AFPSHUD>(HUD);
	// FPSHUD->GameWidgetContainer->SetHealthBar(HealthPercent);

	// Method 2: Get Player Controller
	AFPSHUD* FPSHUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
	FPSHUD->GameWidgetContainer->SetHealthBar(HealthPercent);
}


