// Fill out your copyright notice in the Description page of Project Settings.

#include "RayMarchSet.h"
#include "Engine/CollisionProfile.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ARayMarchSet::ARayMarchSet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	CollisionComponent->InitSphereRadius(35.0f);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetShouldUpdatePhysicsVolume(true);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bDynamicObstacle = true;

	RootComponent = CollisionComponent;

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
		MeshComponent->SetupAttachment(RootComponent);
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

	BlitCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("BlitCamera"));
	BlitCamera->SetupAttachment(RootComponent);
	// set BlitCamera to orthographic type and match unreal plane geometry default size
	BlitCamera->ProjectionType = ECameraProjectionMode::Orthographic;
	BlitCamera->OrthoWidth = 100.0f;

}

// Called when the game starts or when spawned
void ARayMarchSet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARayMarchSet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

