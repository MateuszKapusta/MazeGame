// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "LabiryntTworz.h"
#include "ScianaWewnetrzna.h"
#include "ScianaBoczna.h"
#include "Podloga.h"
#include "LabiryntMeta.h"
#include "LabiryntGameInstance.h"


// Sets default values
ALabiryntTworz::ALabiryntTworz()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StworzLabirynt = CreateDefaultSubobject<UBoxComponent>(TEXT("StworzLabirynt"));
	RootComponent = StworzLabirynt;
}

// Called when the game starts or when spawned
void ALabiryntTworz::BeginPlay()
{
	Super::BeginPlay();

	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

	if (wskaznikGI != NULL)
	{

		int32 x = wskaznikGI->GetIloscX(); //wielkosc tablicy	
		int32 y = wskaznikGI->GetIloscY();
	
		PolaGry.Inicjalizacja(x, y, 0);

		Siatka.Inicjalizacja(x, y * 2 - 1, 1);

		//Trzeba uzupełnić
		//Poprawa  błedu podczas pierszego przypisania wartosci zmienne naprawa bledu z nie uzywana ostatnia zmienna ktora powinna być ustawiona na 0 co 2 wiersz
		for (int32 i = 0; i < Siatka.PoleX[0].PoleY.Num(); i++){

			if (i == 0 || i % 2 == 0){

				Siatka.PoleX[Siatka.PoleX.Num() - 1].PoleY[i] = 0;
			}

		}

		// pozycja charakteru //celuje w srodek ostatniego rzedu jeœli nie blizej prawej
		AlgorytmHuntAndKill((x - 1) / 2, y - 1);

		StworzScianeBocznaIPodloge();
		StworzScianeWewnetrzna();
		UstawLokacjeMety();
		PokarzLabirynt();
	}

}

// Called every frame
void ALabiryntTworz::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}




void ALabiryntTworz::AlgorytmHuntAndKill(int32 startXx,int32 startYy)
{

	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

	if (wskaznikGI != NULL)
	{

		// inicjalicacja Pol startowych wpisywanych do tablicy globalnej
		PolaStartowe.Czysc();

		PolaStartowe.DodajPoleX();

		PolaStartowe.PoleX[0].DodajPoleY(startXx);
		PolaStartowe.PoleX[0].DodajPoleY(startYy);


		//glowna petla algorytmu
		//kiedy HUNT nie zwroci pola pustego , na poczatku mimo tego ze formalnie charaktek jest na polu startowym
		// to zostaje ono zaznaczone dopiero wewnatrz petli

		//zmienne uzywane do polowania jeśli petle  całe przeszły
		int32 i = 0;
		int32 j = 0;
		int32 x = wskaznikGI->GetIloscX(); //wielkosc Labiryntu
		int32 y = wskaznikGI->GetIloscY();
		int32 pozycjaX = startXx;// pozycja charakteru //celuje w srodek ostatniego rzedu jeœli nie blizej prawej
		int32 pozycjaY = startYy;


		while (i + j != x + y){

			while (1){
				//po³ozenie punktu
				PolaGry.PoleX[pozycjaX].PoleY[pozycjaY] = 1;

				int32 sasiedzi[4] = { 0, 0, 0, 0 };
				int32 sasiedziL = 0;

				//dodanie powwojnych if spowodowane błedem przekroczenia indeksów tablicy <- nie sa one potrzebne sprawdzanie w c++ najpierw sprawdza 1 warunek
				// x=5 y=5 poza tablica
				for (int32 k = 0; k<4; k++){

					switch (k){
						//Góra
						case 0:
							if (pozycjaY - 1 >= 0 && PolaGry.PoleX[pozycjaX].PoleY[pozycjaY - 1] == 0)
							{
								sasiedzi[sasiedziL++] = k;
							}
							break;
							//Prawa
						case 1:
							if (pozycjaX + 1 < x && PolaGry.PoleX[pozycjaX + 1].PoleY[pozycjaY] == 0)
							{
								sasiedzi[sasiedziL++] = k;
							}
							break;

						case 2://do
							if (pozycjaY + 1 < y && PolaGry.PoleX[pozycjaX].PoleY[pozycjaY + 1] == 0)
							{
								sasiedzi[sasiedziL++] = k;
							}

							break;
						case 3://lewa
							if (pozycjaX - 1 >= 0 && PolaGry.PoleX[pozycjaX - 1].PoleY[pozycjaY] == 0)
							{
								sasiedzi[sasiedziL++] = k;
							}
							break;
					}

				}

				if (sasiedziL>0){

					//sasiedzi[(rand() + 1) % sasiedziL]
					switch (sasiedzi[FMath::RandRange(0, sasiedziL - 1)]){
						//Góra
						case 0:
						{
							Siatka.PoleX[pozycjaX].PoleY[pozycjaY * 2 - 1] = 0;
							pozycjaY = pozycjaY - 1;
						}
						break;
						//Prawa
						case 1:
						{
							Siatka.PoleX[pozycjaX].PoleY[pozycjaY * 2] = 0;
							pozycjaX = pozycjaX + 1;
						}
						break;

						case 2://dol
						{
							Siatka.PoleX[pozycjaX].PoleY[pozycjaY * 2 + 1] = 0;
							pozycjaY = pozycjaY + 1;
						}
						break;
						case 3://lewa
						{
							Siatka.PoleX[pozycjaX - 1].PoleY[pozycjaY * 2] = 0;
							pozycjaX = pozycjaX - 1;
						}
						break;
					}

				}
				else break;
			}

			// HUNT kod pocześci podobny do poprzedniefgo przejscia po tablicy
			//pole zmienione na 0 umożliwia wyjście z petli
			
			int32 warunekPola = 1;//Sprawdzan nowe wwolne pola

			for (i = 0; i<y && PolaGry.PoleX[pozycjaX].PoleY[pozycjaY] == 1; i++){

				for (j = 0; j<x && PolaGry.PoleX[pozycjaX].PoleY[pozycjaY] == 1; j++){

					if (PolaGry.PoleX[j].PoleY[i] == 0){

						int32 pozycjaYSprawdz = i;
						int32 pozycjaXSprawdz = j;
						int sasiedziH[4] = { 0, 0, 0, 0 };
						int sasiedziLH = 0;

						for (int32 k = 0; k<4; k++){

							switch (k){
								//Gora
								case 0:
									if (pozycjaYSprawdz - 1 >= 0 && PolaGry.PoleX[pozycjaXSprawdz].PoleY[pozycjaYSprawdz - 1] == warunekPola)
									{
										sasiedziH[sasiedziLH++] = k;
									}
									break;
									//Prawa
								case 1:
									if (pozycjaXSprawdz + 1 < x && PolaGry.PoleX[pozycjaXSprawdz + 1].PoleY[pozycjaYSprawdz] == warunekPola){
										sasiedziH[sasiedziLH++] = k;
									}
									break;

								case 2://do³
									if (pozycjaYSprawdz + 1 < y && PolaGry.PoleX[pozycjaXSprawdz].PoleY[pozycjaYSprawdz + 1] == warunekPola){
										sasiedziH[sasiedziLH++] = k;
									}
									break;
								case 3://lewa
									if (pozycjaXSprawdz - 1 >= 0 && PolaGry.PoleX[pozycjaXSprawdz - 1].PoleY[pozycjaYSprawdz] == warunekPola){
										sasiedziH[sasiedziLH++] = k;
									}
									break;
							}
						}

						if (sasiedziLH>0){

							pozycjaY = i;
							pozycjaX = j;

							//sasiedziH[(rand() + 1) % sasiedziLH]
							int32 wyborSasiada = sasiedziH[FMath::RandRange(0, sasiedziLH - 1)];

							switch (wyborSasiada){
								//Góra
								case 0:
								{
									Siatka.PoleX[pozycjaX].PoleY[pozycjaY * 2 - 1] = 0;
								}
								break;
								//Prawa
								case 1:
								{
									Siatka.PoleX[pozycjaX].PoleY[pozycjaY * 2] = 0;
								}
								break;

								case 2://dol
								{
									Siatka.PoleX[pozycjaX].PoleY[pozycjaY * 2 + 1] = 0;
								}
								break;
								case 3://lewa
								{
									Siatka.PoleX[pozycjaX - 1].PoleY[pozycjaY * 2] = 0;
								}
								break;
							}


							//Warunek pola odpowiedzialny za pole start stare
							if (warunekPola == 2){

								int32 zmiennaSx = j;
								int32 zmiennaSy = i;

								switch (wyborSasiada){
									//Góra
									case 0:
									{
										zmiennaSy = zmiennaSy - 1;
									}
									break;
									//Prawa
									case 1:
									{
										zmiennaSx = zmiennaSx + 1;
									}
									break;

									case 2://dó³
									{
										zmiennaSy = zmiennaSy + 1;
									}
									break;
									case 3://lewa
									{
										zmiennaSx = zmiennaSx - 1;
									}
									break;
								}

								PolaStartowe.DodajPoleX();
								PolaStartowe.PoleX[PolaStartowe.PoleX.Num() - 1].DodajPoleY(zmiennaSx);
								PolaStartowe.PoleX[PolaStartowe.PoleX.Num() - 1].DodajPoleY(zmiennaSy);
							}
						}
					}
					

					// sprawdz  teraz  tablice w poszukiwaniu pol postych ktore musza byc dolaczeone do pul starych (z oznaczeniem 2)
					//algorytm darzy do stworzenia tylko jednego polaczenia z  starymi polami 
					if (i + 1 == y && j + 1 == x && warunekPola!=2){

						i = 0;
						j = -1;// sprawdzenie 1 pola=-1
						warunekPola = 2;		
					}

				}
			}

		}


		// Pzywracam  pierszemu polu startowemu wartosc  poprawna , która została zmieniona przez algorytm
		PolaGry.PoleX[startXx].PoleY[startYy] = 2;
		// jesli pole o indeksie 4 4 zostanie wolne  i nie przydzielone do rzadnego innego pola to wartosc w tablicy pozostanie 0 , jest to bład
	}

	return;
}








void  ALabiryntTworz::StworzScianeBocznaIPodloge(){
	
	if (CoStworzycPoBokach != NULL && CoStworzycNaPodlodze != NULL){

		UWorld* const World = GetWorld();

		if (World)
		{		
			ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

			if (wskaznikGI != NULL)
			{
				int32 iloscY = wskaznikGI->GetIloscY();
				int32 iloscX = wskaznikGI->GetIloscX();
				int32 Wielkosc = wskaznikGI->GetWielkosc();

				int32 wartoscX = 0, wartoscY = 0;
				//int32 ileScian = 0;

				wartoscX = (Wielkosc  * iloscX) / 2;//poczatek - polowa obiektu  , obiekt  jest teraz w planszy
				wartoscY = ((Wielkosc  * iloscY) / 2) - (Wielkosc  * iloscY);

				FActorSpawnParameters StworzParametry;
				StworzParametry.Owner = this;
				StworzParametry.Instigator = Instigator;
			
				AScianaBoczna* const StworzonaScianaProbaB = World->SpawnActor<AScianaBoczna>(CoStworzycPoBokach, StworzParametry);

				if (StworzonaScianaProbaB != NULL){

					FVector wskGdzieB;
					FVector wskJakieB;
					int32 wartoscZB = 0;

					StworzonaScianaProbaB->GetActorBounds(false, wskGdzieB, wskJakieB);

					wartoscZB = wskJakieB.Z; //okreslenie Z

					//srodek labiryntu w srodku mapy  
					// zaczynamy od lewego gornego wieszchołka

					FVector StworzLokacjaB = FVector(wartoscX, wartoscY, wartoscZB);
					FRotator StworzRotacjaB = FRotator(0, 0, 0);

					StworzonaScianaProbaB->Destroy();
					
					//lewa x=0 y=-500
					StworzonaScianaB.Add(World->SpawnActor<AScianaBoczna>(CoStworzycPoBokach, StworzLokacjaB - FVector((Wielkosc  * iloscX) / 2, 0, 0), StworzRotacjaB, StworzParametry));
					//prawa //lewa x=0 y=500
					StworzonaScianaB.Add(World->SpawnActor<AScianaBoczna>(CoStworzycPoBokach, StworzLokacjaB - FVector((Wielkosc  * iloscX) / 2, 0, 0) + FVector(0, Wielkosc*iloscY, 0), StworzRotacjaB, StworzParametry));

					StworzRotacjaB.Yaw = 90.0f;

					//gora
					StworzonaScianaB.Add(World->SpawnActor<AScianaBoczna>(CoStworzycPoBokach, StworzLokacjaB + FVector(0, Wielkosc*iloscY / 2, 0), StworzRotacjaB, StworzParametry));
					//prawa //lewa x=0 y=500
					StworzonaScianaB.Add(World->SpawnActor<AScianaBoczna>(CoStworzycPoBokach, StworzLokacjaB - FVector((Wielkosc  * iloscX), 0, 0) + FVector(0, Wielkosc*iloscY / 2, 0), StworzRotacjaB, StworzParametry));


					FVector wskSkalaAktualna;
					float wartoscXSB = 0;

					for (int32 i = 0; i < 4; i++){

						wskSkalaAktualna = StworzonaScianaB[i]->GetActorScale3D();

						//nowa skala=(Wielkosc jaka ma miec obiekt dzielona przez) /(wskJakie.X połowe obiektu*2 / przez skale aktualna) 
						wartoscXSB = (Wielkosc*iloscX) / (wskJakieB.X * 2 / wskSkalaAktualna.X);

						//Nowa skala i zwiekszona wartosc ile scian
						StworzonaScianaB[i]->SetActorScale3D(FVector(wartoscXSB, wskSkalaAktualna.Y, wskSkalaAktualna.Z));
					}
				}	


				// stworzony twstowy element w miejscu 0,0,0  może powodować błędy sprawdzić czy gracz na niego żle reaguje 
				APodloga* const StworzonaPodlogaProba = World->SpawnActor<APodloga>(CoStworzycNaPodlodze, StworzParametry);

				if (StworzonaPodlogaProba != NULL){

					FVector wskGdzieP;
					FVector wskJakieP;
					int32 wartoscZP = 0;

					// połowa kazdej wielkosci
					StworzonaPodlogaProba->GetActorBounds(false, wskGdzieP, wskJakieP);					
					wartoscZP = -wskJakieP.Z*2; //okreslenie -Z // usun 2 przy cube 1_M

					//srodek labiryntu w srodku mapy  
					// zaczynamy od lewego gornego wieszchołka

					FVector StworzLokacjaP = FVector(wartoscX, wartoscY, wartoscZP);
					FRotator StworzRotacjaP = FRotator(0, 90, 0);


					StworzonaPodlogaProba->Destroy();

					int32 wartoscXUzytaP = wartoscX ;
					int32 wartoscYUzytaP = wartoscY ;
					int32 ileScianP = 0;

					for (int32 i = 0; i < iloscY; i++){

						// przygotowanie do ustawiania jednego rzedu

						StworzLokacjaP = FVector(wartoscXUzytaP - Wielkosc / 2, wartoscYUzytaP + Wielkosc / 2, wartoscZP);

						for (int32 j = 0; j < iloscX; j++){

							FVector wskSkalaAktualnaP;
							float wartoscXSP = 0;
							float wartoscYSP = 0;

							// dodaj  sciane
							StworzonaPodloga.Add(World->SpawnActor<APodloga>(CoStworzycNaPodlodze, StworzLokacjaP, StworzRotacjaP, StworzParametry));

							wskSkalaAktualnaP = StworzonaPodloga[ileScianP]->GetActorScale3D();

							//nowa skala=(Wielkosc jaka ma miec obiekt dzielona przez) /(wskJakie.X połowe obiektu*2 / przez skale aktualna) 

							wartoscXSP = Wielkosc / (wskJakieP.X * 2 / wskSkalaAktualnaP.X);

							wartoscYSP = Wielkosc / (wskJakieP.Y * 2 / wskSkalaAktualnaP.Y);

							//Nowa skala i zwiekszona wartosc ile scian
							StworzonaPodloga[ileScianP++]->SetActorScale3D(FVector(wartoscXSP, wartoscYSP, wskSkalaAktualnaP.Z));

							
							StworzLokacjaP = StworzLokacjaP + FVector(0, Wielkosc, 0);  //kwadrat x na x y odpowiedzialne za grobosc

						}

						wartoscXUzytaP = wartoscXUzytaP - Wielkosc;
						wartoscYUzytaP = wartoscY ;

					}

				}
			}
		}
	}

}





void ALabiryntTworz::StworzScianeWewnetrzna()
{

	if (CoStworzycWewnatrz != NULL)
	{

		UWorld* const World = GetWorld();
		if (World)
		{
			ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());

			if (wskaznikGI!=NULL)
			{ 
				int32 iloscY = wskaznikGI->GetIloscY();
				int32 iloscX = wskaznikGI->GetIloscX();
				int32 Wielkosc = wskaznikGI->GetWielkosc();


				int32 wartoscX=0, wartoscY=0, wartoscZ=0;
				int32 ileScian=0;

				FActorSpawnParameters StworzParametry;
				StworzParametry.Owner = this;
				StworzParametry.Instigator = Instigator;

				// stworzony twstowy element w miejscu 0,0,0  może powodować błędy sprawdzić czy gracz na niego żle reaguje 
				AScianaWewnetrzna* const StworzonaScianaProba = World->SpawnActor<AScianaWewnetrzna>(CoStworzycWewnatrz, StworzParametry);


				FVector wskGdzie;
				FVector wskJakie;

				if (StworzonaScianaProba != NULL){

			
					StworzonaScianaProba->GetActorBounds(false, wskGdzie, wskJakie);

					wartoscZ = wskJakie.Z; //okreslenie Z

					// X okresla wielkosc, labirynt jest zawsze  kwadartowy 
					//srodek labiryntu w srodku mapy  
					// zaczynamy od lewego gornego wieszchołka

					wartoscX = (Wielkosc  * iloscX) / 2;//poczatek - polowa obiektu  , obiekt  jest teraz w planszy
					wartoscY = ((Wielkosc  * iloscY) / 2) - (Wielkosc  * iloscY);


					FVector StworzLokacja = FVector(wartoscX, wartoscY, wartoscZ);
					FRotator StworzRotacja = FRotator(0, 0, 0);

					int32 wartoscXUzyta = wartoscX ;
					int32 wartoscYUzyta = wartoscY ;



					StworzonaScianaProba->Destroy();


					// tablica wszystkich csian wewnetrzych możliwość stworzenai zmiennej globalnej latwiejszego dostania sie do scian<- zrobione
					//TArray<AScianaWewnetrzna*>StworzonaSciana;
			
					// inne wspułżedne tabeli a wspolzedne swiata uwazac


					for (int32 i = 0; i < Siatka.PoleX[0].PoleY.Num(); i++){

						// przygotowanie do ustawiania jednego rzedu

						if (i != 0 && i % 2 == 1){			//1


							StworzRotacja.Yaw = 90.0f;

							wartoscYUzyta = wartoscY + Wielkosc ;

							StworzLokacja = FVector(wartoscXUzyta, wartoscYUzyta - Wielkosc/2, wartoscZ);

						}
						else								//0
						{	

							StworzRotacja.Yaw = 0.0f;

							wartoscXUzyta = wartoscXUzyta - Wielkosc ;
							wartoscYUzyta = wartoscY + Wielkosc ;

							StworzLokacja = FVector(wartoscXUzyta + Wielkosc/2, wartoscYUzyta, wartoscZ);
						}
					

						for (int32 j = 0; j < Siatka.PoleX.Num(); j++){

					
							if (Siatka.PoleX[j].PoleY[i] == 1){

								FVector wskSkalaAktualna;
								float wartoscXS = 0;
								
								// dodaj  sciane
								StworzonaSciana.Add(World->SpawnActor<AScianaWewnetrzna>(CoStworzycWewnatrz, StworzLokacja, StworzRotacja, StworzParametry));

								wskSkalaAktualna = StworzonaSciana[ileScian]->GetActorScale3D();

								//nowa skala=(Wielkosc jaka ma miec obiekt dzielona przez) /(wskJakie.X połowe obiektu*2 / przez skale aktualna) 
								wartoscXS = Wielkosc / (wskJakie.X * 2 / wskSkalaAktualna.X);

								//Nowa skala i zwiekszona wartosc ile scian
								StworzonaSciana[ileScian++]->SetActorScale3D(FVector(wartoscXS, wskSkalaAktualna.Y, wskSkalaAktualna.Z));

							}

							StworzLokacja = StworzLokacja + FVector(0, Wielkosc , 0);  //kwadrat x na x y odpowiedzialne za grobosc
						}

					}

				}

			}
		}
	}

}

void ALabiryntTworz::UstawKolorStart(){

	int32 IloscXS=PolaStartowe.PoleX.Num();


	// szerokosc lub wysokosc pol  gry
	int32 IloscYPG = PolaGry.PoleX[0].PoleY.Num();

	for (int32 yt = 0; yt < IloscXS; yt++)
	{

		StworzonaPodloga[PolaStartowe.PoleX[yt].PoleY[0] + (IloscYPG*PolaStartowe.PoleX[yt].PoleY[1])]->ZmienKolorStart();

	}
}

void ALabiryntTworz::UstawLokacjeMety(){


	ULabiryntGameInstance* wskaznikGI = Cast<ULabiryntGameInstance>(GetGameInstance());
	int32 x = wskaznikGI->GetIloscX(); //wielkosc Labiryntu
	int32 y = wskaznikGI->GetIloscY();

	FPoleXIntTablica PolaDrogiMety;

	//przepisanie wartosci starych korytarzy do nowej tablicy
	PolaDrogiMety.Inicjalizacja(x, y, 0);
	PolaDrogiMety.Kopiuj(PolaGry);

	int32 IloscStartow = PolaStartowe.PoleX.Num();

	FPoleXIntTablica WlasciwaDroga;

	WlasciwaDroga.Czysc();


	for (int32 i = 0; i < IloscStartow; i++)
	{	
			
		int32 poczatekX = PolaStartowe.PoleX[i].PoleY[0];
		int32 poczatekY = PolaStartowe.PoleX[i].PoleY[1];
		int32 iloscPunktow = 0;
		FPoleXIntTablica TempDroga;
		TempDroga.Czysc();

		while (1){

			//po³ozenie punktu //0 odwiedzone//2 stare//1 dostempne

			PolaDrogiMety.PoleX[poczatekX].PoleY[poczatekY] = 0;

			iloscPunktow++;

			//UE_LOG(LogTemp, Warning, TEXT("Srat %d     %d		%d"), poczatekX, poczatekY, iloscPunktow);

			int32 sasiedzi[4] = { 0, 0, 0, 0 };
			int32 sasiedziL = 0;

			//dodanie powwojnych if spowodowane błedem przekroczenia indeksów tablicy <- nie sa one potrzebne sprawdzanie w c++ najpierw sprawdza 1 warunek
			
			for (int32 k = 0; k<4; k++){

				switch (k){
						//Góra
					case 0:
						if (poczatekY - 1 >= 0 && PolaDrogiMety.PoleX[poczatekX].PoleY[poczatekY - 1] == 1 && Siatka.PoleX[poczatekX].PoleY[poczatekY * 2 - 1]==0)
						{
							sasiedzi[sasiedziL++] = k;
						}
						break;
						//Prawa
					case 1:
						if (poczatekX + 1 < x && PolaDrogiMety.PoleX[poczatekX + 1].PoleY[poczatekY] == 1 && Siatka.PoleX[poczatekX].PoleY[poczatekY * 2]==0)
						{
							sasiedzi[sasiedziL++] = k;
						}
						break;

					case 2://do
						if (poczatekY + 1 < y && PolaDrogiMety.PoleX[poczatekX].PoleY[poczatekY + 1] == 1 && Siatka.PoleX[poczatekX].PoleY[poczatekY * 2 + 1] == 0)
						{
							sasiedzi[sasiedziL++] = k;
						}

						break;
					case 3://lewa
						if (poczatekX - 1 >= 0 && PolaDrogiMety.PoleX[poczatekX - 1].PoleY[poczatekY] == 1 && Siatka.PoleX[poczatekX - 1].PoleY[poczatekY * 2] == 0)
						{
							sasiedzi[sasiedziL++] = k;
						}
						break;
				}
			}


			if (sasiedziL>0){

				int32 tempPoczatekX = poczatekX;
				int32 tempPoczatekY = poczatekY;

				// wartosc w tablicy sasiedzi ktora została dodana do niej jako piersza 
				//gora prawa dol lewa

				switch (sasiedzi[0]){
					//Gora
					case 0:
					{
						poczatekY = poczatekY - 1;
					}
					break;
					//Prawa
					case 1:
					{
						poczatekX = poczatekX + 1;
					}
					break;

					case 2://dol
					{
						poczatekY = poczatekY + 1;
					}
					break;
					case 3://lewa
					{
						poczatekX = poczatekX - 1;
					}
					break;
					}
			

				int32 iloscD = 0;

				if (sasiedziL > 1){
				
					for (int32 l = 1; l < sasiedziL;l++)

						switch (sasiedzi[l]){
							//Góra
							case 0:
							{							
								TempDroga.DodajPoleX();
							//	UE_LOG(LogTemp, Warning, TEXT("Srat %d     "), TempDroga.PoleX.Num() - 1);
								iloscD = TempDroga.PoleX.Num() - 1;

								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekX);
								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekY - 1);
								TempDroga.PoleX[iloscD].DodajPoleY(iloscPunktow);
							}
							break;
							//Prawa
							case 1:
							{
								TempDroga.DodajPoleX();
								//UE_LOG(LogTemp, Warning, TEXT("Srat %d     "), TempDroga.PoleX.Num() - 1);
								iloscD = TempDroga.PoleX.Num() - 1;

								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekX + 1);
								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekY);
								TempDroga.PoleX[iloscD].DodajPoleY(iloscPunktow);
							}
							break;

							case 2://dol
							{
								TempDroga.DodajPoleX();
								//UE_LOG(LogTemp, Warning, TEXT("Srat %d     "), TempDroga.PoleX.Num() - 1);
								iloscD = TempDroga.PoleX.Num() - 1;

								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekX);
								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekY+ 1);
								TempDroga.PoleX[iloscD].DodajPoleY(iloscPunktow);

							}
							break;
							case 3://lewa
							{
								TempDroga.DodajPoleX();
								//UE_LOG(LogTemp, Warning, TEXT("Srat %d     "), TempDroga.PoleX.Num() - 1);
								iloscD = TempDroga.PoleX.Num() - 1;

								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekX - 1);
								TempDroga.PoleX[iloscD].DodajPoleY(tempPoczatekY);
								TempDroga.PoleX[iloscD].DodajPoleY(iloscPunktow);
							}
							break;
						}
				
				}
		
			}
			else
			{
				
				
				WlasciwaDroga.DodajPoleX();

				int32 iloscD = WlasciwaDroga.PoleX.Num() - 1;
				WlasciwaDroga.PoleX[iloscD].DodajPoleY(poczatekX);
				WlasciwaDroga.PoleX[iloscD].DodajPoleY(poczatekY);
				WlasciwaDroga.PoleX[iloscD].DodajPoleY(iloscPunktow);
			
				if (TempDroga.PoleX.Num() != 0){
				
					
					poczatekX=TempDroga.PoleX[TempDroga.PoleX.Num() - 1].PoleY[0];
					poczatekY=TempDroga.PoleX[TempDroga.PoleX.Num() - 1].PoleY[1];
					iloscPunktow=TempDroga.PoleX[TempDroga.PoleX.Num() - 1].PoleY[2];
					TempDroga.PoleX[TempDroga.PoleX.Num() - 1].PoleY.Empty();

					TempDroga.PoleX.Pop();
					//or RemoveAt(TempDroga.PoleX.Num()-1);

				// Przelamanie petki while rozpoczecie kolejnego pola startowego
				}
				else{
					//UE_LOG(LogTemp, Warning, TEXT("Przerwa"));
				 break;
				}
						
			}
				
		}

	}


	
	int32 indeks = 0;
	int32 najwiekszaW = 0;

	for (int32 K = 0; K<WlasciwaDroga.PoleX.Num(); K++){
	
	
		if (najwiekszaW < WlasciwaDroga.PoleX[K].PoleY[2]){
		
			najwiekszaW = WlasciwaDroga.PoleX[K].PoleY[2];
			indeks = K;
		}
	
	
	}
	
	FVector wskGdzieP;
	FVector wskJakieP;

	StworzonaPodloga[WlasciwaDroga.PoleX[indeks].PoleY[0] + (x*WlasciwaDroga.PoleX[indeks].PoleY[1])]->GetActorBounds(false, wskGdzieP, wskJakieP);
	
	FVector wskGdzieM;
	FVector wskJakieM;


	for (TObjectIterator<ALabiryntMeta> ZnajdzMeta; ZnajdzMeta; ++ZnajdzMeta)
	{
		ZnajdzMeta->GetActorBounds(false, wskGdzieM, wskJakieM);

		ZnajdzMeta->SetActorLocation(FVector(wskGdzieP.X, wskGdzieP.Y, wskGdzieM.Z));
	}
}





void ALabiryntTworz::ScianyKolejnaRunda(){
	
	//Stworzone Sciany wewnetrzne
	//Scian bocznych i podlogi nie niszczymy sa nam potrzebne


	for (int32 i = 0; i < StworzonaSciana.Num(); i++){

		StworzonaSciana[i]->Destroy();
	}

	StworzonaSciana.Empty();

	//Pola labiryntu
	PolaGry.Ustaw(0);

	//Siatka Labiryntu
	Siatka.Ustaw(1);

	//Trzeba uzupełnić
	//Poprawa  błedu podczas pierszego przypisania wartosci zmienne naprawa bledu z nie uzywana ostatnia zmienna ktora powinna być ustawiona na 0 co 2 wiersz
	for (int32 i = 0; i < Siatka.PoleX[0].PoleY.Num(); i++){

		if (i == 0 || i % 2 == 0){

			Siatka.PoleX[Siatka.PoleX.Num() - 1].PoleY[i] = 0;
		}
	}

	


	int32 IloscXPG = PolaGry.PoleX.Num();
	int32 IloscYPG = PolaGry.PoleX[0].PoleY.Num();

	int32 IleWSacisadow;

	TArray<int32> NaBrzegachX;
	TArray<int32> NaBrzegachY;

	// poprawa nowej siatki i polgry 
	for (int32 yt = 0; yt < IloscYPG; yt++)
	{
		for (int32 xv = 0; xv < IloscXPG; xv++)
		{

			if (StworzonaPodloga[xv + (IloscYPG*yt)]->GetOdwiedzony() == true){

				PolaGry.PoleX[xv].PoleY[yt] = 2;// zmienione z 1 na  2 ,  lacz sie  tylko w razie potrzeby ze starymi odwiedzonymi
			
				IleWSacisadow = 0;

				// uzupelnienie nowej siatki ,jesli ma polaczenia z odwiedzonymi  zniszcz sciane
				for (int32 k = 0; k<4; k++){

					switch (k){
						//Góra
						case 0:
							if (yt - 1 >= 0 && StworzonaPodloga[xv + (IloscYPG*(yt - 1))]->GetOdwiedzony() == true)
							{

								Siatka.PoleX[xv].PoleY[yt * 2 - 1] = 0;

							}// warunek sprawdzony poraz drugi poniewaz
							//musimy wiedziec czy spowodowany jest on krawedziom czy brakiem sasiada
							else if (yt - 1 >= 0){

									IleWSacisadow = IleWSacisadow + 1;	
							}

						break;
					
							//Prawa
						case 1:
					
							if (xv + 1 <IloscXPG && StworzonaPodloga[xv + 1 + (IloscYPG*yt)]->GetOdwiedzony() == true)
							{
								Siatka.PoleX[xv].PoleY[yt * 2] = 0;
							}
							else if (xv + 1 < IloscXPG){

									IleWSacisadow = IleWSacisadow + 1;
							
							}
						break;
					
						case 2://do
							if (yt + 1 < IloscYPG && StworzonaPodloga[xv  + (IloscYPG*(yt + 1))]->GetOdwiedzony() == true)
							{
								Siatka.PoleX[xv].PoleY[yt * 2 + 1] = 0;
							}
							else if (yt + 1 < IloscYPG){

									IleWSacisadow = IleWSacisadow + 1;
							}
						

						break;
					
						case 3://lewa
					
							if (xv - 1 >= 0 && StworzonaPodloga[xv - 1 + (IloscYPG*yt )]->GetOdwiedzony())
							{
								Siatka.PoleX[xv - 1].PoleY[yt * 2] = 0;
							}
							else if (xv - 1 >= 0){

									IleWSacisadow = IleWSacisadow + 1;
							}
						
						break;					
					}
				}


				if (IleWSacisadow > 0){
					NaBrzegachX.Add(xv);
					NaBrzegachY.Add(yt);
				}
			
	
			}
				
		}

	}


	// Wywolanie metod----------------------------------------------------------------------------------------------


	//odwolanie sie do nowo uzupełnionej tablicy nie zmieniać kolejnosci

	//Szukanie odwiedzonego miejsca w labiryncie jeśli  uda mu sie trafic na miejsce na krawedzi polaczone z nie odwiedzonym miejscem dobrze 
	//w innym wypadku polaczenie z lewej gornej strony odwiedzonych mniejsc

	int32 zmiennaX ;
	int32 zmiennaY ;
	int32 losowaBG;
	
	//losowa wartosc z tablicy wartosci na brzegu 


	losowaBG=FMath::RandRange(0, NaBrzegachX.Num() - 1);

	zmiennaX = NaBrzegachX[losowaBG];
	zmiennaY = NaBrzegachY[losowaBG];


	
	AlgorytmHuntAndKill(zmiennaX, zmiennaY);

	StworzScianeWewnetrzna();

	UstawKolorStart();

	UstawLokacjeMety();
	//---------------------------------------------
	NaBrzegachX.Empty();
	NaBrzegachY.Empty();

	PokarzLabirynt();

}



void FPoleXIntTablica::Czysc(){
	{
		if (PoleX.Num() <= 0) return;

		//Empty
		for (int32 v = 0; v < PoleX.Num(); v++)
		{
			PoleX[v].PoleY.Empty();
		}
		PoleX.Empty();
	}

}

void FPoleXIntTablica::Ustaw(int32 Wartosc){
	
	if (PoleX.Num() <= 0) return;

	const int32 IloscX = PoleX.Num();
	const int32 IloscY = PoleX[0].PoleY.Num();

		
	for (int32 t = 0; t < IloscX; t++)
	{
		for (int32 v = 0; v < IloscY; v++)
		{
			PoleX[t].PoleY[v] = Wartosc;
		}

	}
		
}




void FPoleXIntTablica::Kopiuj(FPoleXIntTablica Wartosc){

	if (PoleX.Num() <= 0) return;
	//Tablice musza miec takie same wielkosci
	if ((PoleX.Num() != Wartosc.PoleX.Num()) || (PoleX[0].PoleY.Num() != Wartosc.PoleX[0].PoleY.Num())) return;


	const int32 IloscX = PoleX.Num();
	const int32 IloscY = PoleX[0].PoleY.Num();


	for (int32 t = 0; t < IloscX; t++)
	{
		for (int32 v = 0; v < IloscY; v++)
		{
			PoleX[t].PoleY[v] = Wartosc.PoleX[t].PoleY[v];
		}

	}

}





void FPoleXIntTablica::Inicjalizacja(const int32 LicznikX, const int32 LicznikY, int32 Wartosc)
{
	//Add Kolumn
	for (int32 v = 0; v < LicznikX; v++)
	{
		DodajPoleX();
	}

	//Add Kolumny
	for (int32 v = 0; v < LicznikX; v++)
	{
		for (int32 b = 0; b < LicznikY; b++)
		{
			PoleX[v].DodajPoleY(Wartosc);
		}
	}
}

void FPoleXIntTablica::DodajPoleX()
{
	PoleX.Add(FPoleYInt());
}


void FPoleYInt::DodajPoleY(int32 Wartosc)
{
	PoleY.Add(Wartosc);
}