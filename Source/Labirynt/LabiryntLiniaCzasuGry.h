// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LabiryntLiniaCzasuGry.generated.h"

UCLASS()
class LABIRYNT_API ALabiryntLiniaCzasuGry : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabiryntLiniaCzasuGry();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FTimeline LiniaCzasuGry;

	UFUNCTION()
		void  PodczasGry(float Value);

	UFUNCTION()
		void UstawLabirynt(float Value);

	UFUNCTION()
		void  UstawKamere(float Value);

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		float  GetCzasRundy();
	
	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		float  GetCzasGry();


private:
	// Na lini czasu petle kamery i labiryntu wykonuja sie raz 
	int32  sprawdzKamera;
	int32  sprawdzLabirynt;

	int32 liczbaRundLCG;
	// wystarczy raz pobrac wartosc na poczatku rundy
	int32  czasZegaraRundyLCG;

	FTimerHandle LicznikKameraGornaC;
	FTimerHandle LicznikKameraGornaU;
	FTimerHandle LicznikLabiryntTworz;


};
