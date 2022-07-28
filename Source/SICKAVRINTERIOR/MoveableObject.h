// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "MoveableObject.generated.h"

UCLASS()
class SICKAVRINTERIOR_API AMoveableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BindToInput();

	void ConsumeMovementInput();

protected:
	/** dummy USceneComponent as Root */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Dummy;

	/** The mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;


	/**
	 * Accumulated control input vector, stored in world space. This is the pending input, which is cleared (zeroed) once consumed.
	 */
	UPROPERTY(Transient)
	FVector ControlInputVector;

	UPROPERTY(Transient)
	FRotator RotationInput;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	virtual void MoveForward(float Val);

	UFUNCTION(BlueprintCallable)
	virtual void MoveRight(float Val);

	UFUNCTION(BlueprintCallable)
	virtual void AddYawInput(float Val);

	/*
	* Dummy function to intercept and consume input event
	*/
	UFUNCTION(BlueprintCallable)
	virtual void AddPitchInput(float Val);

};
