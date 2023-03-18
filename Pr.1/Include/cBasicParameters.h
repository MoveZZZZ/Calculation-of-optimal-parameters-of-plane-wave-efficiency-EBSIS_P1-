#pragma once
class cBasicParameters
{
protected:
	double czestotliwosc;
	double szerokoscPlyty; 
	double dlugoscPlyty; 
	double minimalnaSkutecznosc;
	double maksymalnaSkutecznosc;

public:
	cBasicParameters();
	cBasicParameters(double aCzestotliwosc, double aDlugoscPlyty, double aSzerokoscPlyty, double aMinSkutecznosc, double aMaxSkutecznosc);

	double getCzestotliwosc();
	double getSzerokoscPlyty();
	double getDlugoscPlyty();
	double getMinimalnaSkutecznosc();
	double getMaksymalnaSkutecznosc();
};

