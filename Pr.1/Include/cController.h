#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include<stdlib.h>
#include "cDane.h"
#include "dodatkoweOtwory.h"
class cController
{
private: 
    double czestotliwosc;
    const double predkoscSwiatla = 299792458; // m/s
    double dlugoscFali; // m
    double szerokoscPlyty; //m
    double dlugoscPlyty; //m

    double przekatnaMinimalna; //m
    double przekatnaMaksymalna;//m
    //--------------------------------------------------------------------------------------------------------------
    double maksymalnaSkutecznosc;
    double minimalnaSkutecznosc;

    double odlegloscPomiedzyOdcinkami;

    int polozenie;

    int menu;
    const std::string plik = "ResultTxt/DanePolozenie";
    const std::string koniecPliku = ".txt";

    std::vector<cDane> dataStorage;
    std::vector<dodatkoweOtwory> v_dodatkoweOtwory;

    std::string fileName; 

    double* wierszyIkolumnyOdcinek;
    double* wierszyIkolumnyPlyta;

    double szerokoscOdcinku;
    double dlugoscOdcinku;

    double pozostalyOdcinekPionowySzerekosc;
    double pozostalyOdcinekPionowyDlugosc;

    double pozostalyOdcinekPoziomySzerekosc;
    double pozostalyOdcinekPoziomyDlugosc;

    bool odstepPlyta;


public: 
    cController(double aCzestotliwosc, double aDlugoscPlyty, double aSzerokoscPlyty, double aMinSkutecznosc, double aMaxSkutecznosc,  bool aOdstepPlyta, bool aZmianaPrzek, double aNewPrzekatna);
    cController();
    void writeResultFiles();
    void vectorSort();

    void wierszyOrazKolumnyOdcinkowNaPlycie();

    double* wierszyOrazKolumnyNaOdcinkuTrojkatProsty(double odstepPomiedzyOtworami, double przyprostokatna);
    double* wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(double odstepPomiedzyOtworami, double przyprostokatna);
    double* wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(double odstepPomiedzyOtworami, double przyprostokatna, double przeciwprostokatna);
    double* wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(double odstepPomiedzyOtworami, double przyprostokatna, double przeciwprostokatna);
    void dodatkoweOtworyNaPlycie(double przekatna, double odstepOtwory);
    double poleOtworow(double liczbaOtworow, double przyprostokatna);
    void obliczenieParametrow();
    void addData(double aPrzekatnaTymczasowa, double aSkutecznosc, double aOdstepPomiedzyOtworamiWOdcinku, double aPrzyprostokatna, double aLiczbaOtworow);

    void createFileName(std::string temp);
    void startCalculation(int aPolozenie);
    void printData();

};

