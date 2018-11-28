// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LabiryntTworz.generated.h"


USTRUCT()
struct FPoleYInt
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<int32>  PoleY;

	void DodajPoleY(int32 Wartosc);

	FPoleYInt()
	{
	}
};




USTRUCT()
struct FPoleXIntTablica
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<FPoleYInt> PoleX;

	void DodajPoleX();
	void Inicjalizacja(const int32 LicznikY, const int32 LicznikX, int32 Wartosc);
	void Czysc();
	void Ustaw(int32 Wartosc);
	void Kopiuj(FPoleXIntTablica Wartosc);


	FPoleXIntTablica()
	{
	}
};




UCLASS()
class LABIRYNT_API ALabiryntTworz : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabiryntTworz();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	FORCEINLINE class UBoxComponent* GetStworzLabirynt() const { return StworzLabirynt; }


	//Efekt znikania
	UFUNCTION(BlueprintImplementableEvent, Category = "Efent")
	void UkryjLabirynt();


	//Efekt znikania
	UFUNCTION(BlueprintImplementableEvent, Category = "Efent")
	void PokarzLabirynt();

protected:
	
	UPROPERTY(EditAnywhere, Category = "Tworzenie Powierzchni")
	TSubclassOf<class AScianaWewnetrzna> CoStworzycWewnatrz;

	UPROPERTY(EditAnywhere, Category = "Tworzenie Powierzchni")
	TSubclassOf<class AScianaBoczna> CoStworzycPoBokach;

	UPROPERTY(EditAnywhere, Category = "Tworzenie Powierzchni")
	TSubclassOf<class APodloga> CoStworzycNaPodlodze;


	FPoleXIntTablica PolaStartowe;

	FPoleXIntTablica PolaGry;
	TArray<APodloga*>StworzonaPodloga;


	FPoleXIntTablica Siatka;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zmienna Gry")
	TArray<AScianaWewnetrzna*>StworzonaSciana;

	TArray<AScianaBoczna*>StworzonaScianaB;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tworzenie", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* StworzLabirynt;
	

	void UstawKolorStart();

	void AlgorytmHuntAndKill(int32 startXx, int32 startYy);

	void StworzScianeBocznaIPodloge();

	void StworzScianeWewnetrzna();

	void UstawLokacjeMety();

public:

	void ScianyKolejnaRunda();


};



