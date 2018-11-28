// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Podloga.generated.h"

UCLASS()
class LABIRYNT_API APodloga : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APodloga();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FORCEINLINE class UStaticMeshComponent* GetPodlogaMesh() const { return PodlogaMesh; }

	// zmienia kolor podlogi
	UFUNCTION(BlueprintImplementableEvent, Category = "Efent")
	void ZmienKolor();

	// zmienia kolor podlogi
	UFUNCTION(BlueprintImplementableEvent, Category = "Efent")
	void ZmienKolorStart();


	void SetOdwiedzony(bool wartosc);	
	bool GetOdwiedzony();



private:

	bool Odwiedzony = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Powierzchnia", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PodlogaMesh;

	
};
