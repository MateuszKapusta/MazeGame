// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "KameraGorna.generated.h"

/**
*
*/
UCLASS()
class LABIRYNT_API AKameraGorna : public ACameraActor
{
	GENERATED_BODY()


public:
	AKameraGorna();

	virtual void BeginPlay() override;

	void UstawKamere();
	void CofnijKamere();


	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
	void SetKGornaWartosc(int32 wartosc);

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
	int32 GetKGornaWartosc();

protected:

	AActor* ViewTempPodstawowy;
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
	int32 KGornaWartosc;

};
