#include "..\Include\cDane.h"

cDane::cDane(double aPrzekatna, double aSkutecznosc)
{
	przekatna = aPrzekatna;
	skutecznosc = aSkutecznosc;
}

double cDane::getIloscOtwarc()
{
	return iloscOtwarc;
}
void cDane::setIloscOtwarc(double aOtwarcia)
{
	iloscOtwarc = aOtwarcia;
}


double cDane::getPrzekatna()
{
	return przekatna;
}


double cDane::getSkutecznosc()
{
	return skutecznosc;
}

double cDane::getOdleglosc()
{
	return odleglosc;
}
void cDane::setOdleglosc(double aOdleglosc)
{
	odleglosc = aOdleglosc;
}
double cDane::getWierszy()
{
	return wierszy;
}
void cDane::setWierszy(double aWierszy)
{
	wierszy = aWierszy;
}
double cDane::getKolumny()
{
	return kolumny;
}
void cDane::setKolumny(double aKolumny)
{
	kolumny = aKolumny;
}
double cDane::getPole()
{
	return pole;
}
void cDane::setPole(double aPole)
{
	pole = aPole;
}

double cDane::getWierszyOdcinek()
{
	return wierszeOdcinek;
}
void cDane::setWierszyOdcinek(double aWierszyOdcinek)
{
	wierszeOdcinek = aWierszyOdcinek;
}

double cDane::getKolumnyOdcinek()
{
	return kolumnyOdcinek;
}
void cDane::setKolumnyOdcinek(double aKolumnyOdcinek)
{
	kolumnyOdcinek = aKolumnyOdcinek;
}

double cDane::getDodatkoweOtworyPionW()
{
	return dodatkoweOtworyPionW;
}

void cDane::setDodatkoweOtworyPionW(double aWierszePionoweDodatkowe)
{
	dodatkoweOtworyPionW = aWierszePionoweDodatkowe;
}

double cDane::getDodatkoweOtworyPionK()
{
	return dodatkoweOtworyPionK;
}

void cDane::setDodatkoweOtworyPionK(double aKolumnyPionoweDodatkowe)
{
	dodatkoweOtworyPionK = aKolumnyPionoweDodatkowe;
}

double cDane::getDodatkoweOtworyPozW()
{
	return dodatkoweOtworyPozW;
}

void cDane::setDodatkoweOtworyPozW(double aWierszePoziomeDodatkowe)
{
	dodatkoweOtworyPozW = aWierszePoziomeDodatkowe;
}

double cDane::getDodatkoweOtworyPozK()
{
	return dodatkoweOtworyPozK;
}

void cDane::setDodatkoweOtworyPozK(double aKolumnyPoziomeDodatkowe)
{
	dodatkoweOtworyPozK = aKolumnyPoziomeDodatkowe;
}

double cDane::getDodatkoweOdcinkiPozioma()
{
	return dodatkoweOdcinekiPozioma;
}

void cDane::setDodatkoweOdcinkiPozioma(double aDodatkoweOdcinkiPozioma)
{
	dodatkoweOdcinekiPozioma = aDodatkoweOdcinkiPozioma;
}

double cDane::getDodatkoweOdcinkiPionowa()
{
	return dodatkoweOdcinekiPionowa;
}

void cDane::setDodatkoweOdcinkiPionowa(double aDodatkoweOdcinkiPionowa)
{
	dodatkoweOdcinekiPionowa = aDodatkoweOdcinkiPionowa;
}
