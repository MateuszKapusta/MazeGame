// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sciana.generated.h"

UCLASS()
class LABIRYNT_API ASciana : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASciana();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UStaticMeshComponent* GetScianaMesh() const { return ScianaMesh; }


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Powierzchnia", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ScianaMesh;


};
