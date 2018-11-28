// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "LabiryntMeta.h"
#include "LabiryntGameInstance.h"
#include "LabiryntGameMode.h"
// Sets default values
ALabiryntMeta::ALabiryntMeta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MetaMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MetaMesh"));
	RootComponent = MetaMesh;

	MetaMesh->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void ALabiryntMeta::BeginPlay()
{
	Super::BeginPlay();
	
	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());


	// dopasowanie wielkosci mety do reszty labiryntu

	int32 iloscX = wskaznikGI->GetIloscX();
	int32 iloscY = wskaznikGI->GetIloscY();
	int32 Wielkosc = wskaznikGI->GetWielkosc();

	FVector wskSkalaAktualna;
	float wartoscX = 0;
	float wartoscY= 0;

	FVector wskGdzieP;
	FVector wskJakieP;

	this->GetActorBounds(false, wskGdzieP, wskJakieP);
	wskSkalaAktualna = this->GetActorScale3D();

	//nowa skala=(Wielkosc jaka ma miec obiekt dzielona przez) /(wskJakie.X po³owe obiektu*2 / przez skale aktualna) 

	wartoscX = Wielkosc / (wskJakieP.X * 2 / wskSkalaAktualna.X);
	wartoscY= Wielkosc / (wskJakieP.Y * 2 / wskSkalaAktualna.Y);

	//Nowa skala 
	this->SetActorScale3D(FVector(wartoscX, wartoscY, wskSkalaAktualna.Z));

	//Nowe polorzenie
	//this->SetActorLocation(FVector(Wielkosc*iloscX / 2 - Wielkosc/2, 0, wskGdzieP.Z));

}

// Called every frame
void ALabiryntMeta::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}


