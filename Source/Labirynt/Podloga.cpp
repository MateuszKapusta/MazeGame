// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "Podloga.h"


// Sets default values
APodloga::APodloga()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PodlogaMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("PodlogaMesh"));
	RootComponent = PodlogaMesh;

	PodlogaMesh->SetSimulatePhysics(true);


}

// Called when the game starts or when spawned
void APodloga::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APodloga::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APodloga::SetOdwiedzony(bool wartosc){

	Odwiedzony = wartosc;
};


bool APodloga::GetOdwiedzony(){

	return Odwiedzony;
};