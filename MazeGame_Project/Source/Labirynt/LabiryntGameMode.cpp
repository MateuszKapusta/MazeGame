// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Labirynt.h"
#include "LabiryntGameMode.h"
#include "LabiryntCharacter.h"
#include "LabiryntGameInstance.h"
#include "LabiryntMeta.h"
#include "Podloga.h"

ALabiryntGameMode::ALabiryntGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = false;
}



// Called when the game starts or when spawned
void ALabiryntGameMode::BeginPlay()
{
	Super::BeginPlay();
}



void  ALabiryntGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




AActor* ALabiryntGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<APlayerStart*> UnOccupiedStartPoints;
	TArray<APlayerStart*> OccupiedStartPoints;

	FActorSpawnParameters SpawnInfo;

	//kompilator ma z tym problem
	//SpawnInfo.bNoCollisionFail = true;

	SpawnInfo.Owner = this;
	SpawnInfo.Instigator = NULL;
	SpawnInfo.bDeferConstruction = false;


	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

	int32 iloscX = wskaznikGI->GetIloscX();
	int32 Wielkosc = wskaznikGI->GetWielkosc();


	LabiryntPlayerStart = GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), FVector(-((iloscX*Wielkosc)/2-Wielkosc/2), 0, 92), FRotator::ZeroRotator, SpawnInfo);


	if (LabiryntPlayerStart == NULL)
	{
		if (UnOccupiedStartPoints.Num() > 0)
		{
			LabiryntPlayerStart = UnOccupiedStartPoints[FMath::RandRange(0, UnOccupiedStartPoints.Num() - 1)];
		}
		else if (OccupiedStartPoints.Num() > 0)
		{
			LabiryntPlayerStart = OccupiedStartPoints[FMath::RandRange(0, OccupiedStartPoints.Num() - 1)];
		}
	}


	return LabiryntPlayerStart;
}
	


void ALabiryntGameMode::WygranaNowyPoziom() {

	// Zwieksza wartosc pod koniec rozgrywki przed wczytaniem sie naspepnego poziomu
	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

	int32 licznikPoziom = wskaznikGI->GetLicznikPoziom();
	int32 iloscX = wskaznikGI->GetIloscX();
	int32 iloscY = wskaznikGI->GetIloscY();
	int32 licznikRund = wskaznikGI->GetLicznikDodRund();

	//zalezne od licznik poziom ustawic przed poziomem
	if (licznikPoziom % 3 == 0) wskaznikGI->SetLicznikDodRund(licznikRund + 1);

	iloscX = iloscX + 2;
	iloscY = iloscY + 2;

	wskaznikGI->SetIloscX(iloscX);
	wskaznikGI->SetIloscY(iloscY);

	licznikPoziom = licznikPoziom + 1;
	wskaznikGI->SetLicznikPoziom(licznikPoziom);

	UWorld* const World = GetWorld();
	ALabiryntGameMode* wskaznikGM = (ALabiryntGameMode*)World->GetAuthGameMode();

	//Zrestartowanie gry
	wskaznikGM->RestartGame();
}

void ALabiryntGameMode::PrzegranaStaryPoziom() {

	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());
	wskaznikGI->SetIloscZyc(wskaznikGI->GetIloscZyc() - 1);

	if (wskaznikGI->GetIloscZyc()<=0) {

		ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());
		wskaznikGI->SetDefault();

		UWorld* const World = GetWorld();
		ALabiryntGameMode* wskaznikGM = (ALabiryntGameMode*)World->GetAuthGameMode();

		//Zrestartowanie gry
		wskaznikGM->RestartGame();
	}
}