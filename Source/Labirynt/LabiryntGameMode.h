// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "LabiryntGameMode.generated.h"


UCLASS(minimalapi)
class ALabiryntGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALabiryntGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	APlayerStart* LabiryntPlayerStart;

protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UFUNCTION(BlueprintCallable, Category = "Pickups")
		void SprawdzPodloge();

	void ZacznijNowyPoziom();

};



