// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "LabiryntGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LABIRYNT_API ULabiryntGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULabiryntGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetDefault();

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		int32 GetIloscX();

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		int32 GetIloscY();

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		int32 GetWielkosc();

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		int32 GetLicznikPoziom();

	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetIloscX(int32 wartosc);

	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetIloscY(int32 wartosc);

	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetWielkosc(int32 wartosc);

	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetLicznikPoziom(int32 wartosc);
	
	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetLicznikDodRund(int32 wartosc);

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		int32 GetLicznikDodRund();

	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetCzasZegaraRundy(int32 wartosc);

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		int32 GetCzasZegaraRundy();

	UFUNCTION(BlueprintPure, Category = "UstawieniaGry")
		int32 GetIloscZyc();

	UFUNCTION(BlueprintCallable, Category = "UstawieniaGry")
		void SetIloscZyc(int32 wartosc);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
		int32 iloscX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
		int32 iloscY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
		int32 wielkosc;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
		int32 licznikPoziom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
		int32 licznikDodRund;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
		int32 iloscZyc;

	//wartosc powinna byc ustawiona zaleznie od krawedzi czasu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZmienneGry")
		int32 czasZegaraRundy;

};
