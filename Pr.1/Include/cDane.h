#pragma once
class cDane
{
private: 
	double iloscOtwarc; 
	double przekatna;
	double skutecznosc;
	double odleglosc; 
	double wierszy;
	double kolumny; 
	double wierszeOdcinek; 
	double kolumnyOdcinek; 
	double pole;

	double dodatkoweOtworyPionW;
	double dodatkoweOtworyPionK;

	double dodatkoweOtworyPozW;
	double dodatkoweOtworyPozK;

	double dodatkoweOdcinekiPionowa;
	double dodatkoweOdcinekiPozioma;
	
public: 
	cDane(double aPrzekatna, double aSkutecznosc);

	double getIloscOtwarc();
	void setIloscOtwarc(double aOtwarcia);

	double getPrzekatna();

	double getSkutecznosc();

	double getOdleglosc();
	void setOdleglosc(double aOdleglosc);

	double getWierszy();
	void setWierszy(double aWierszy);

	double getKolumny();
	void setKolumny(double aKolumny);

	double getPole();
	void setPole(double aPole);

	double getWierszyOdcinek();
	void setWierszyOdcinek(double aWierszyOdcinek);

	double getKolumnyOdcinek();
	void setKolumnyOdcinek(double aKolumnyOdcinek);

	double getDodatkoweOtworyPionW();
	void setDodatkoweOtworyPionW(double aWierszePionoweDodatkowe);

	double getDodatkoweOtworyPionK();
	void setDodatkoweOtworyPionK(double aKolumnyPionoweDodatkowe);

	double getDodatkoweOtworyPozW();
	void setDodatkoweOtworyPozW(double aWierszePoziomeDodatkowe);

	double getDodatkoweOtworyPozK();
	void setDodatkoweOtworyPozK(double aKolumnyPoziomeDodatkowe);

	double getDodatkoweOdcinkiPozioma();
	void setDodatkoweOdcinkiPozioma(double aDodatkoweOdcinkiPozioma);
	
	double getDodatkoweOdcinkiPionowa();
	void setDodatkoweOdcinkiPionowa(double aDodatkoweOdcinkiPionowa);
};

