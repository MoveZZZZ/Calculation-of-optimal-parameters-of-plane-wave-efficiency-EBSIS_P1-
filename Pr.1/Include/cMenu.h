#pragma once
#include<iostream>
#include "../Include/cController.h"
class cMenu
{
private:
	int menu;
	double czestotliwosc; 
	double dlugoscPlyty;
	double szerokoscPlyty; 
	double minimalnaSkutecznosc;
	double maksymalnaSkutecznosc;
	double polozenie; 
	double polozenieStart; 
	double przekatnaMinimalna;

	int odstepOdGranic;
	int przekatnaZmiana;

	bool bPrzekatnaZmiana;
	bool bOdstepOdGranic;

	
public:
	cMenu();
	void printMenu();
	void printCase1();
	void printCase2();
};

