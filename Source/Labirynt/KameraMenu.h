// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Podloga.h"
#include "Camera/CameraActor.h"
#include "KameraMenu.generated.h"

/**
 * 
 */
UCLASS()
class LABIRYNT_API AKameraMenu : public ACameraActor
{
	GENERATED_BODY()


public:
	AKameraMenu();
	virtual void BeginPlay() override;
	
protected:

	AActor* ViewTempPodstawowy;
	APlayerController* PlayerController;
};
