// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RayMarchSet.generated.h"





UCLASS()
class SICKAVRINTERIOR_API ARayMarchSet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARayMarchSet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	/** Blit Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneCaptureComponent2D* BlitCamera;

private:
	/** collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> CollisionComponent;

	/** The mesh associated with this. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
