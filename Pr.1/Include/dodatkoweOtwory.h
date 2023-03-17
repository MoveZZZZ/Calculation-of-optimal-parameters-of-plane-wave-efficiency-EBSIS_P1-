#pragma once
class dodatkoweOtwory
{
private:
	double otworyPionoweWiersze; 
	double otworyPionoweKolumny;
	double otworyPoziomeWiersze;
	double otworyPoziomeKolumny;
	double iloscOdcinkowPionowa;
	double iloscOdcinkowPozioma;

public: 
	dodatkoweOtwory(double aOPNW, double aOPNK, double aOPZW, double aOPZK, double aIOPN, double aIOPZ);
	double getOtworyPionoweWiersze();
	double getOtworyPionoweKolumny();
	double getOtworyPoziomeWiersze();
	double getOtworyPoziomeKolumny();
	double getIloscOdcinkowPionowe();
	double getIloscOdcinkowPoziome();
};

