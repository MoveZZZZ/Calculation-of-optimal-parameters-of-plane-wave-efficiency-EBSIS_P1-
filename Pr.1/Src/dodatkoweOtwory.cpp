#include "../Include/dodatkoweOtwory.h"

dodatkoweOtwory::dodatkoweOtwory(double aOPNW, double aOPNK, double aOPZW, double aOPZK, double aIOPN, double aIOPZ)
{
	otworyPionoweWiersze = aOPNW;
	otworyPionoweKolumny = aOPNK;

	otworyPoziomeWiersze = aOPZW;
	otworyPoziomeKolumny = aOPZK;

	iloscOdcinkowPionowa = aIOPN;
	iloscOdcinkowPozioma = aIOPZ;
}

double dodatkoweOtwory::getOtworyPionoweWiersze()
{
	return otworyPionoweWiersze;
}
double dodatkoweOtwory::getOtworyPionoweKolumny()
{
	return otworyPionoweKolumny;
}

double dodatkoweOtwory::getOtworyPoziomeWiersze()
{
	return otworyPoziomeWiersze;
}

double dodatkoweOtwory::getOtworyPoziomeKolumny()
{
	return otworyPoziomeKolumny;
}

double dodatkoweOtwory::getIloscOdcinkowPionowe()
{
	return iloscOdcinkowPionowa;
}

double dodatkoweOtwory::getIloscOdcinkowPoziome()
{
	return iloscOdcinkowPozioma;
}
