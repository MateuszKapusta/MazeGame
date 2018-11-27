// Fill out your copyright notice in the Description page of Project Settings.

#include "Labirynt.h"
#include "LabiryntGameInstance.h"


ULabiryntGameInstance::ULabiryntGameInstance(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
	SetDefault();
}

void ULabiryntGameInstance::SetDefault() {

	iloscX = 5;
	iloscY = 5;
	wielkosc = 400;
	licznikPoziom = 1;
	licznikDodRund = 0;
	czasZegaraRundy = 46;
	iloscZyc = 3;
}


int32  ULabiryntGameInstance::GetIloscX(){

	return iloscX;
}

int32 ULabiryntGameInstance::GetIloscY(){

	return iloscY;
}

int32 ULabiryntGameInstance::GetWielkosc(){

	return wielkosc;
}

int32 ULabiryntGameInstance::GetLicznikPoziom(){

	return licznikPoziom;
}

void  ULabiryntGameInstance::SetIloscX(int32 wartosc){

	iloscX=wartosc;
}

void ULabiryntGameInstance::SetIloscY(int32 wartosc){

	iloscY = wartosc;
}

void ULabiryntGameInstance::SetWielkosc(int32 wartosc){

	wielkosc = wartosc;
}

void ULabiryntGameInstance::SetLicznikPoziom(int32 wartosc){

	licznikPoziom = wartosc;
}


void ULabiryntGameInstance::SetLicznikDodRund(int32 wartosc){

	licznikDodRund = wartosc;
}


int32 ULabiryntGameInstance::GetLicznikDodRund(){

	return licznikDodRund;
}
	

void ULabiryntGameInstance::SetCzasZegaraRundy(int32 wartosc){

	czasZegaraRundy = wartosc;
}


int32 ULabiryntGameInstance::GetCzasZegaraRundy(){

	return czasZegaraRundy;
}

int32 ULabiryntGameInstance::GetIloscZyc()
{
	return iloscZyc;
}

void ULabiryntGameInstance::SetIloscZyc(int32 wartosc)
{
	iloscZyc = wartosc;
}
