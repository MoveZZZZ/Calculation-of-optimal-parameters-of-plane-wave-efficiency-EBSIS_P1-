#include<cmath>
#include "..\Include\cBasicParameters.h"

cBasicParameters::cBasicParameters()
{
	czestotliwosc = 1.56 * pow(10, 9); // Hz  //1.56
	dlugoscPlyty = 0.5;
	szerokoscPlyty = 0.5;
	minimalnaSkutecznosc = 20.0;
	maksymalnaSkutecznosc = 100.0;
}

cBasicParameters::cBasicParameters(double aCzestotliwosc, double aDlugoscPlyty, double aSzerokoscPlyty, double aMinSkutecznosc, double aMaxSkutecznosc)
{
    czestotliwosc = aCzestotliwosc * pow(10, 9);
    dlugoscPlyty = aDlugoscPlyty;
    szerokoscPlyty = aSzerokoscPlyty;
    minimalnaSkutecznosc = aMinSkutecznosc;
    maksymalnaSkutecznosc = aMaxSkutecznosc;
}

double cBasicParameters::getCzestotliwosc()
{
	return czestotliwosc;
}

double cBasicParameters::getSzerokoscPlyty()
{
	return szerokoscPlyty;
}

double cBasicParameters::getDlugoscPlyty()
{
	return dlugoscPlyty;
}

double cBasicParameters::getMinimalnaSkutecznosc()
{
	return minimalnaSkutecznosc;
}

double cBasicParameters::getMaksymalnaSkutecznosc()
{
	return maksymalnaSkutecznosc;
}
