// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LabiryntMeta.generated.h"

UCLASS()
class LABIRYNT_API ALabiryntMeta : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabiryntMeta();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FORCEINLINE class UStaticMeshComponent* GetMetaMesh() const { return MetaMesh; }




private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Prze³¹cznik", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MetaMesh;
		
};
