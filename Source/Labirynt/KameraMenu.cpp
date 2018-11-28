// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "KameraMenu.h"
#include "LabiryntGameInstance.h"

#include "Podloga.h"

AKameraMenu::AKameraMenu()
{
}

void AKameraMenu::BeginPlay()
{
	Super::BeginPlay();

	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

	int32 iloscX ;
	int32 iloscY ;
	int32 Wielkosc ;


	if (wskaznikGI != NULL)
	{
		iloscX = wskaznikGI->GetIloscX();
		iloscY = wskaznikGI->GetIloscY();
		Wielkosc = wskaznikGI->GetWielkosc();
		this->SetActorRotation(FRotator(0, 0, 0));
		this->SetActorLocation(FVector(-iloscX / 2 * Wielkosc + Wielkosc/2, 0, 20));		
	}


	
	PlayerController = GetWorld()->GetFirstPlayerController();
	ViewTempPodstawowy = PlayerController->GetViewTarget();

	if (PlayerController && ViewTempPodstawowy)
	{
		PlayerController->SetViewTarget(this);
	}
	
	//Gracz nie mo¿e siê poruszaæ w menu , dodatkowe zabezpieczenie 
	APlayerController* PlayerUstawienia = UGameplayStatics::GetPlayerController(this, 0);
	PlayerUstawienia->SetIgnoreMoveInput(true);
	ACharacter* PlayerSkok = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerSkok->GetMesh()->SetSimulatePhysics(true);
	PlayerSkok->GetMovementComponent()->MovementState.bCanJump = false;
	
}
