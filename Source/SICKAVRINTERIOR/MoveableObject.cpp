// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableObject.h"
#include "GameFramework/InputSettings.h"

// Sets default values
AMoveableObject::AMoveableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Dummy = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent0"));
	RootComponent = Dummy;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh;
		FConstructorStatics()
			: Mesh(TEXT("/Engine/BasicShapes/Cube")) {}
	};

	static FConstructorStatics ConstructorStatics;

	MeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent0"));
	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(ConstructorStatics.Mesh.Object);
		MeshComponent->AlwaysLoadOnClient = true;
		MeshComponent->AlwaysLoadOnServer = true;
		MeshComponent->bCastDynamicShadow = true;
		MeshComponent->bAffectDynamicIndirectLighting = true;
		MeshComponent->bAffectDistanceFieldLighting = true;
		MeshComponent->bVisibleInRayTracing = true;
		MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

		MeshComponent->SetGenerateOverlapEvents(false);
		MeshComponent->SetCanEverAffectNavigation(false);

		MeshComponent->SetMobility(EComponentMobility::Movable);
	}
}

// Called when the game starts or when spawned
void AMoveableObject::BeginPlay()
{
	Super::BeginPlay();
	
	BindToInput();
}

// Called every frame
void AMoveableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ConsumeMovementInput();
}


void AMoveableObject::BindToInput()
{
	// Initialize uinput component
	InputComponent = NewObject<UInputComponent>(this, UInputSettings::GetDefaultInputComponentClass(), TEXT("ActorInputComponent0"));
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		// Bind inputs here
		// InputComponent->BindAction("Jump", IE_Pressed, this, &AUnrealisticPawn::Jump);
		// etc...


		InputComponent->BindAxis("MoveForward", this, &AMoveableObject::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AMoveableObject::MoveRight);
		InputComponent->BindAxis("Turn", this, &AMoveableObject::AddYawInput);
		InputComponent->BindAxis("LookUp", this, &AMoveableObject::AddPitchInput);



		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		//EnableInput(GetWorld()->GetFirstPlayerController());
	}
}


void AMoveableObject::MoveForward(float Val)
{
	if (Val != 0.f)
	{
		float scale = 2.0f;
		ControlInputVector.X += Val * scale;
	}
}


void AMoveableObject::MoveRight(float Val)
{
	if (Val != 0.f)
	{	
		float scale = 2.0f;
		ControlInputVector.Y += Val * scale;	
	}
}


void AMoveableObject::AddYawInput(float Val)
{
	if (Val != 0.f)
	{
		float scale = 2.0f;
		RotationInput.Yaw += Val * scale;
	}
}


void AMoveableObject::AddPitchInput(float Val)
{
}

void AMoveableObject::ConsumeMovementInput()
{
	if (ControlInputVector != FVector::ZeroVector)
	{
		AddActorWorldOffset(ControlInputVector);
		ControlInputVector = FVector::ZeroVector;
	}

	if (RotationInput != FRotator::ZeroRotator)
	{
		AddActorWorldRotation(RotationInput);
		RotationInput = FRotator::ZeroRotator;
	}
}