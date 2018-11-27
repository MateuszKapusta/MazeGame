// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "Sciana.h"


// Sets default values
ASciana::ASciana()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ScianaMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("ScianaMesh"));
	RootComponent = ScianaMesh;

	ScianaMesh->SetSimulatePhysics(true);

}


// Called when the game starts or when spawned
void ASciana::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASciana::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

