#pragma once
#include<iostream>
#include "../Include/cController.h"
class cMenu: public cBasicParameters
{
private:
	int menu;
	double polozenie; 
	double polozenieStart; 
	double przekatnaMinimalna;

	int odstepOdGranic;
	int przekatnaZmiana;

	bool bPrzekatnaZmiana;
	bool bOdstepOdGranic;

	
public:
	cMenu();
	void startPage();
	void printMenu();
	void printCase1();
	void printCase2();
};

