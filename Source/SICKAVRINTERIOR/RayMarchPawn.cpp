// Fill out your copyright notice in the Description page of Project Settings.


#include "RayMarchPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ARayMarchPawn::ARayMarchPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseEyeHeight = 0.0f;
	bCollideWhenPlacing = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent0"));
	CollisionComponent->InitSphereRadius(35.0f);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetShouldUpdatePhysicsVolume(true);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bDynamicObstacle = true;

	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	MovementComponent->UpdatedComponent = CollisionComponent;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	/*BillBoardComponent = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("MaterialBillboardCom"));
	BillBoardComponent->SetupAttachment(RootComponent);*/

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Engine/BasicShapes/Plane")) {}
	};

	static FConstructorStatics ConstructorStatics;

	MeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent0"));
	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(ConstructorStatics.PlaneMesh.Object);
		MeshComponent->AlwaysLoadOnClient = true;
		MeshComponent->AlwaysLoadOnServer = true;
		MeshComponent->bCastDynamicShadow = false;
		MeshComponent->bAffectDynamicIndirectLighting = false;
		MeshComponent->bAffectDistanceFieldLighting = false;
		MeshComponent->bVisibleInRayTracing = false;
		MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		MeshComponent->SetupAttachment(CameraComp);
		MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

		//const float Scale = CollisionComponent->GetUnscaledSphereRadius() / 160.f; // @TODO: hardcoding known size of EngineMeshes.Sphere. Should use a unit sphere instead.
		//MeshComponent->SetRelativeScale3D(FVector(Scale));
		MeshComponent->SetGenerateOverlapEvents(false);
		MeshComponent->SetCanEverAffectNavigation(false);

		FVector Position;
		Position.X = 50.0f;
		Position.Y = 0.0f;
		Position.Z = 0.0f;

		FRotator Rotation;
		Rotation.Yaw = 0.0f;
		Rotation.Pitch = 90.0f;
		Rotation.Roll = 0.0f;

		MeshComponent->SetMobility(EComponentMobility::Movable);
		MeshComponent->SetRelativeLocationAndRotation(Position, Rotation);
	}
}

// Called when the game starts or when spawned
void ARayMarchPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARayMarchPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARayMarchPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARayMarchPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARayMarchPawn::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ARayMarchPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ARayMarchPawn::AddControllerYawInput);
}

UPawnMovementComponent* ARayMarchPawn::GetMovementComponent() const
{
	return MovementComponent;
}


void ARayMarchPawn::MoveForward(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
		}
	}
}

void ARayMarchPawn::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
		}
	}
}



