// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "KameraGorna.h"
#include "LabiryntGameInstance.h"
#include "LabiryntCharacter.h"

AKameraGorna::AKameraGorna()
{
}


void AKameraGorna::BeginPlay()
{
	Super::BeginPlay();

	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

	if (wskaznikGI != NULL)
	{
		int32 iloscX = wskaznikGI->GetIloscX();
		int32 iloscY = wskaznikGI->GetIloscY();
		int32 Wielkosc = wskaznikGI->GetWielkosc();
		int32 Poziom = wskaznikGI->GetLicznikPoziom();

		this->SetActorLocation(FVector(0, 0, iloscX*Wielkosc + 200-Poziom*80));
		this->SetActorRotation(FRotator(270, 0, 0));
	}


	UstawKamere();
}



void AKameraGorna::UstawKamere(){

	SetKGornaWartosc(1);


	for (TObjectIterator<ALabiryntCharacter> ZnajdzCharacter; ZnajdzCharacter; ++ZnajdzCharacter)
	{
		ZnajdzCharacter->WlSwiatloKolor();
	}


	PlayerController = GetWorld()->GetFirstPlayerController();
	ViewTempPodstawowy = PlayerController->GetViewTarget();



	if (PlayerController && ViewTempPodstawowy)
	{
		PlayerController->SetViewTarget(this);
	}


	//Gracz nie mo¿e siê poruszaæ podczas pokazywania labiryntu
	APlayerController* PlayerUstawienia = UGameplayStatics::GetPlayerController(this, 0);
	PlayerUstawienia->SetIgnoreMoveInput(true);
	ACharacter* PlayerSkok = UGameplayStatics::GetPlayerCharacter(this, 0);	
	PlayerSkok->GetMesh()->SetSimulatePhysics(true);
	PlayerSkok->GetMovementComponent()->MovementState.bCanJump = false;
}

void  AKameraGorna::CofnijKamere(){

	SetKGornaWartosc(0);

	//ustaw migotanie gracza
	for (TObjectIterator<ALabiryntCharacter> ZnajdzCharacter; ZnajdzCharacter; ++ZnajdzCharacter)
	{
		ZnajdzCharacter->WylSwiatloKolor();
	}


	if (PlayerController && ViewTempPodstawowy)
	{
		PlayerController->SetViewTarget(ViewTempPodstawowy);
	}


	//Gracz mo¿e siê poruszaæ
	APlayerController* PlayerUstawienia = UGameplayStatics::GetPlayerController(this, 0);
	PlayerUstawienia->SetIgnoreMoveInput(false);
	ACharacter* PlayerSkok = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerSkok->GetMesh()->SetSimulatePhysics(true);
	PlayerSkok->GetMovementComponent()->MovementState.bCanJump = true;	
}

void AKameraGorna::SetKGornaWartosc(int32 wartosc){

	KGornaWartosc = wartosc;
}


int32 AKameraGorna::GetKGornaWartosc(){

	return KGornaWartosc;
}