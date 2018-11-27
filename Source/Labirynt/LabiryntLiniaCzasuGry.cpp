// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "LabiryntLiniaCzasuGry.h"
#include "LabiryntGameInstance.h"
#include "LabiryntGameMode.h"
#include "LabiryntTworz.h"
#include "KameraGorna.h"


#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

// Sets default values
ALabiryntLiniaCzasuGry::ALabiryntLiniaCzasuGry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	sprawdzKamera = 0;
	sprawdzLabirynt = 0;

	const ConstructorHelpers::FObjectFinder<UCurveFloat> CzasGry(TEXT("Float Curve '/Game/BlueprintsLabirynt/Krzywe/CzasGry.CzasGry'"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat> Kamera(TEXT("Float Curve '/Game/BlueprintsLabirynt/Krzywe/Kamera.Kamera'"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat> Labirynt(TEXT("Float Curve '/Game/BlueprintsLabirynt/Krzywe/Labirynt.Labirynt'"));

	LiniaCzasuGry = FTimeline{};
	FOnTimelineFloat metoda1{};
	FOnTimelineFloat metoda2{};
	FOnTimelineFloat metoda3{};

	metoda1.BindUFunction(this, "PodczasGry");
	LiniaCzasuGry.AddInterpFloat(CzasGry.Object, metoda1, FName{ TEXT("PodczasGry") });

	metoda2.BindUFunction(this, "UstawKamere");
	LiniaCzasuGry.AddInterpFloat(Kamera.Object, metoda2, FName{ TEXT("Kamera") });

	metoda3.BindUFunction(this, "UstawLabirynt");
	LiniaCzasuGry.AddInterpFloat(Labirynt.Object, metoda3, FName{ TEXT("Labirynt") });
}

// Called when the game starts or when spawned
void ALabiryntLiniaCzasuGry::BeginPlay()
{
	Super::BeginPlay();

	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());
	liczbaRundLCG = wskaznikGI->GetLicznikDodRund();

	czasZegaraRundyLCG = wskaznikGI->GetCzasZegaraRundy();

	LiniaCzasuGry.PlayFromStart();
}

// Called every frame
void ALabiryntLiniaCzasuGry::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	if (LiniaCzasuGry.IsPlaying())
	{
		LiniaCzasuGry.TickTimeline(DeltaTime);
	}

}




float  ALabiryntLiniaCzasuGry::GetCzasRundy(){

	float wartosc = 0;
	wartosc = (czasZegaraRundyLCG - LiniaCzasuGry.GetPlaybackPosition())/2.0;

	// nie ma wartosci ujemnych kiedy zmiada kamery 
	if (wartosc < 0) wartosc = 0.00;

	return wartosc;
}



float  ALabiryntLiniaCzasuGry::GetCzasGry(){

	float wartosc = 0;
	wartosc =( czasZegaraRundyLCG - LiniaCzasuGry.GetPlaybackPosition())/2.0;
	// nie ma wartosci ujemnych kiedy zmiada kamery 
	if (wartosc < 0) wartosc = 0.00;

	return wartosc + (czasZegaraRundyLCG/2.0)*liczbaRundLCG;
}






void  ALabiryntLiniaCzasuGry::PodczasGry(float Value){

		//zerowanie wartosci odpowiedzialnych za nie wlaczanie w tej samej rundzie 2 razy z rzedu metody na poczatku rundy 
	if ((int32)Value == 0 ){

		sprawdzLabirynt = 0;
		sprawdzKamera = 0;
	}

}



void  ALabiryntLiniaCzasuGry::UstawLabirynt(float Value)
{
	if ((int32)Value == 1 && sprawdzLabirynt != (int32)Value&&liczbaRundLCG== 0){
		for (TObjectIterator<ALabiryntTworz> ZnajdzLabiryntTworz; ZnajdzLabiryntTworz; ++ZnajdzLabiryntTworz)
		{	
			sprawdzLabirynt = Value;		
			ZnajdzLabiryntTworz->UkryjLabirynt();
			GetWorldTimerManager().SetTimer(LicznikLabiryntTworz, *ZnajdzLabiryntTworz, &ALabiryntTworz::ScianyKolejnaRunda, 2, false);
		}

		//PRZEGRALES
		ALabiryntGameMode* gmPointer = (ALabiryntGameMode*)GetWorld()->GetAuthGameMode();
		gmPointer->PrzegranaStaryPoziom();
	}


	if ((int32)Value == -1 &&  sprawdzLabirynt != (int32)Value){

	
		
		if (liczbaRundLCG == 0) {

			ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());
			liczbaRundLCG = wskaznikGI->GetLicznikDodRund();
		}
		else{
			
			liczbaRundLCG = liczbaRundLCG - 1;
		}

		sprawdzLabirynt = Value;

		LiniaCzasuGry.SetNewTime(0.0);

	}

}



void  ALabiryntLiniaCzasuGry::UstawKamere(float Value)
{

	if ((int32)Value == -1.0 && sprawdzKamera != (int32)Value) {

		sprawdzKamera = Value;

		for (TObjectIterator<AKameraGorna> ZnajdzKameraGorna; ZnajdzKameraGorna; ++ZnajdzKameraGorna)
		{
			GetWorldTimerManager().SetTimer(LicznikKameraGornaC, *ZnajdzKameraGorna, &AKameraGorna::CofnijKamere, 0.001, false);

		}
	}

	if ((int32)Value == 1.0 && sprawdzKamera != (int32)Value){

		sprawdzKamera = Value;
		
		for (TObjectIterator<AKameraGorna> ZnajdzKameraGorna; ZnajdzKameraGorna; ++ZnajdzKameraGorna)
		{
			GetWorldTimerManager().SetTimer(LicznikKameraGornaU, *ZnajdzKameraGorna, &AKameraGorna::UstawKamere, 0.001, false);

		}
		
	}
}