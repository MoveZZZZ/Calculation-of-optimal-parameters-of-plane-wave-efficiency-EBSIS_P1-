#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include<stdlib.h>
#include "Include/cDane.h"
#include "Include/dodatkoweOtwory.h"
using namespace std;
//-----------------------------------------------------------
void writeFile(vector<cDane> daneLAST, double czestotliwosc, double szerPl, double dlPl, double skutS, double skutE, double przS, double przE, string fileName, int polozenieOtworow, double odlPomOdc)
{
    sort(daneLAST.begin(), daneLAST.end(), [](cDane& a, cDane& b) -> bool
        {
            return a.getPole() > b.getPole();
        });
    double dlugoscFali = 299792458 / czestotliwosc; //m
    ofstream out; 
    out.open(fileName);
    if (out.is_open())
    {
        out << "*********DANE POCATKOWE*********" << endl;
        out << "Czestotliwosc(Hz): " << czestotliwosc << ", rozmiar plyty(cm): " << dlPl * 100 << "x" << szerPl*100 << endl;
        out << "Rozmiar odcinku(cm): " << (dlugoscFali / 2 )*100<<"x"<< (dlugoscFali/ 2) * 100<<", odleglosc pomiedzy odc.(cm):"<<odlPomOdc*100<< endl;
        out << "Zakres skutecznosci(dB), od: " << skutS << " do " << skutE << endl;
        out << "Przekatna(cm), od: " << przS*100 << " do " << przE*100 << endl;
        out << "Polozenie: " << polozenieOtworow<<endl;
        out << "***************************************************************************" << endl;
        for(int i=0; i<daneLAST.size(); i++)
        {
            out << "Liczba odcinkow na plycie: " << daneLAST[i].getWierszy() * daneLAST[i].getKolumny() << ", wierszy: " << daneLAST[i].getWierszy() << ", kolumny: " << daneLAST[i].getKolumny() << endl;
            out << "Odleglosc pomiędzy odcinkami(cm): " << odlPomOdc * 100 << endl;
            out << "Liczba otworów na odcinku: "<<daneLAST[i].getWierszyOdcinek()*daneLAST[i].getKolumnyOdcinek() << ", wierszy: " << daneLAST[i].getWierszyOdcinek() << ", kolumny: " << daneLAST[i].getKolumnyOdcinek() << endl;
            out << "Odleglosc pomiędzy otworami(cm): " << daneLAST[i].getOdleglosc()*100 << "; przekatna(cm): " << daneLAST[i].getPrzekatna()*100 << endl;
            out << "Otrzymana skutecznosc(dB):" << daneLAST[i].getSkutecznosc()<<"\nCalkowita ilosc otworow(dodatkowe): "<<daneLAST[i].getIloscOtwarc()<<"("<<daneLAST[i].getDodatkoweOtworyPionK()*daneLAST[i].getDodatkoweOtworyPionW()*daneLAST[i].getDodatkoweOdcinkiPionowa()
                +daneLAST[i].getDodatkoweOtworyPozK()*daneLAST[i].getDodatkoweOtworyPozW()*daneLAST[i].getDodatkoweOdcinkiPozioma()<<")" << ", całkowite pole otworów(cm^2): " << daneLAST[i].getPole() * 10000 << endl;
            out << "Dodatkowe odcinki, linia pionowa: " << daneLAST[i].getDodatkoweOdcinkiPionowa() << endl;
            out << "Dodatkowe otwory, odcinek linia pionowa: " << daneLAST[i].getDodatkoweOtworyPionK() * daneLAST[i].getDodatkoweOtworyPionW() << ", wierszy: " << daneLAST[i].getDodatkoweOtworyPionW() << ", kolumny: " << daneLAST[i].getDodatkoweOtworyPionK() << endl;
            out << "Dodatkowe odcinki, linia pozioma: " << daneLAST[i].getDodatkoweOdcinkiPozioma() << endl;
            out << "Dodatkowe otwory, odcinek linia pozioma: " << daneLAST[i].getDodatkoweOtworyPozK() * daneLAST[i].getDodatkoweOtworyPozW() << ", wierszy: " << daneLAST[i].getDodatkoweOtworyPozW() << ", kolumny: " << daneLAST[i].getDodatkoweOtworyPozK() << endl;
            out << "---------------------------------------------------------------------------" << endl;
        }
    }

}
void showVector(vector<cDane> data)
{
    sort(data.begin(), data.end(), [](cDane& a, cDane& b) -> bool
        {
            return a.getSkutecznosc() < b.getSkutecznosc();
        });
    for (int i = 0; i < data.size(); i++)
    {
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Otwory: " << data[i].getIloscOtwarc() << ", skut.: " << data[i].getSkutecznosc() << ", przekatna: " << data[i].getPrzekatna() * 100 << endl;
        cout << "w.: " << data[i].getWierszy() << ", k.: " << data[i].getKolumny() << ", odl.: " << data[i].getOdleglosc() * 100 << ", pole: " << data[i].getPole() * 10000 << endl;
    }
}
double* wierszyOrazKolumnyNaOdcinkuTrojkatProsty(double szerokoscOdcinku, double dlugoscOdcinku, double odstepPomiedzyOtworami, double przyprostokatna)
{
    double* parametryWK = new double[2];
    parametryWK[0] = floor((szerokoscOdcinku+odstepPomiedzyOtworami)/(przyprostokatna+odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = floor((dlugoscOdcinku + odstepPomiedzyOtworami) / (przyprostokatna + odstepPomiedzyOtworami)); //liczba kolumn
    return parametryWK;
}
double* wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(double szerokoscOdcinku, double dlugoscOdcinku, double odstepPomiedzyOtworami, double przyprostokatna)
{
    double* parametryWK = new double[2];
    parametryWK[0] = floor((szerokoscOdcinku+odstepPomiedzyOtworami)/(przyprostokatna+odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = 2*floor((dlugoscOdcinku + odstepPomiedzyOtworami) / (przyprostokatna + 2*odstepPomiedzyOtworami)); //liczba kolumn
    if (parametryWK[1]/2*(przyprostokatna+2*odstepPomiedzyOtworami)+przyprostokatna<=dlugoscOdcinku)
    {
        parametryWK[1] += 1;
    }
    return parametryWK;
}
double* wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(double szerokoscOdcinku, double dlugoscOdcinku, double odstepPomiedzyOtworami, double przyprostokatna, double przeciwprostokatna)
{
    double* parametryWK = new double[2];
    double wysokosc = (przyprostokatna * sqrt(2)) / 2;
    parametryWK[0] = floor((szerokoscOdcinku+odstepPomiedzyOtworami)/(wysokosc+odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = floor((dlugoscOdcinku + odstepPomiedzyOtworami) / (przeciwprostokatna + odstepPomiedzyOtworami)); //liczba kolumn
    return parametryWK;
}
double* wierszyOrazKolumnyOdcinkowNaPlycie(double szerokoscPlyty, double dlugoscPlyty, double odstepPomiedzyOdcinkami, double szerokoscOdcinku, double dlugoscOdcinku)
{
    double* parametryWK = new double[2];
    parametryWK[0] = floor((szerokoscPlyty /*- odstepPomiedzyOdcinkami*/) / (szerokoscOdcinku + odstepPomiedzyOdcinkami)); //liczba wierszy
    parametryWK[1] = floor((dlugoscPlyty /*- odstepPomiedzyOdcinkami*/) / (dlugoscOdcinku + odstepPomiedzyOdcinkami)); //liczba kolumn 
    return parametryWK;
}
double* wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(double szerokoscOdcinku, double dlugoscOdcinku, double odstepPomiedzyOtworami, double przyprostokatna, double przeciwprostokatna)
{
    double* parametryWK = new double[2];
    double wysokosc = (przyprostokatna * sqrt(2)) / 2;
    parametryWK[0] = floor((szerokoscOdcinku + odstepPomiedzyOtworami) / (wysokosc + odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = floor((dlugoscOdcinku + odstepPomiedzyOtworami+2*przeciwprostokatna) / (przeciwprostokatna + odstepPomiedzyOtworami)); //liczba kolumn
    if (int(parametryWK[1]) %2 == 0)
    {
        parametryWK[1] -= 1;
    }
    if (((parametryWK[1]-2)*przeciwprostokatna+parametryWK[1]*odstepPomiedzyOtworami + przeciwprostokatna/2)<= dlugoscOdcinku)
    {
        parametryWK[1] += 1;
    }
    return parametryWK;
}
vector<dodatkoweOtwory> dodatkoweOtworyNaPlycie(double szerokoscPlyty, double dlugoscPlyty,  double wkOdcinkow[], double odstepOdcinki, double odstepOtwory, double przekatna, double dlOdcinku, double szOdcinku, int polozenie, double lambda)
{
    double pozostalaDlugoscPlyty = dlugoscPlyty - wkOdcinkow[1] * (dlOdcinku + odstepOdcinki);
    double pozostalaSzerokoscPlyty = szerokoscPlyty - wkOdcinkow[0] * (szOdcinku + odstepOdcinki);

    double pozostalyOdcinekPionowyDlugosc = lambda / 2;
    double  pozostalyOdcinekPionowyDlugoscCalkowita= szerokoscPlyty - pozostalaSzerokoscPlyty;
    //
    double pozostalyOdcinekPionowySzerekosc =  pozostalaDlugoscPlyty;

    double pozostalyOdcinekPoziomyDlugosc = lambda / 2;
    double pozostalyOdcinekPoziomyDlugoscCalkowita = dlugoscPlyty; 
    //
    double pozostalyOdcinekPoziomySzerekosc = pozostalaSzerokoscPlyty;

    double* dodatkoweOtworyPionowe = new double[2]; //odcinek Pionowy
    double* dodatkoweOtworyPoziome = new double[2]; //odcinek Poziomy

    vector<dodatkoweOtwory> data;

    double przyprostokatna = przekatna / sqrt(2);

    double iloscOdcinkowPionowa = floor((pozostalyOdcinekPionowyDlugoscCalkowita) / (pozostalyOdcinekPionowyDlugosc + lambda / 10));
    double iloscOdcinkowPozioma = floor((pozostalyOdcinekPoziomyDlugoscCalkowita) / (pozostalyOdcinekPoziomyDlugosc + lambda / 10));
    if (polozenie == 1)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatProsty(pozostalyOdcinekPionowySzerekosc, pozostalyOdcinekPionowyDlugosc, odstepOtwory, przyprostokatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatProsty(pozostalyOdcinekPoziomySzerekosc, pozostalyOdcinekPoziomyDlugosc, odstepOtwory, przyprostokatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        data.push_back(dodatkoweOtworyTemp);
    }
    else if (polozenie == 2)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(pozostalyOdcinekPionowySzerekosc, pozostalyOdcinekPionowyDlugosc, odstepOtwory, przyprostokatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(pozostalyOdcinekPoziomySzerekosc, pozostalyOdcinekPoziomyDlugosc, odstepOtwory, przyprostokatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        data.push_back(dodatkoweOtworyTemp);
    }
    else if (polozenie == 3)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(pozostalyOdcinekPionowySzerekosc, pozostalyOdcinekPionowyDlugosc, odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(pozostalyOdcinekPoziomySzerekosc, pozostalyOdcinekPoziomyDlugosc, odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        data.push_back(dodatkoweOtworyTemp);
    }
    else if (polozenie == 4)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(pozostalyOdcinekPionowySzerekosc, pozostalyOdcinekPionowyDlugosc, odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(pozostalyOdcinekPoziomySzerekosc, pozostalyOdcinekPoziomyDlugosc, odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        data.push_back(dodatkoweOtworyTemp);
    }
    return data;
}
double poleOtworow(double liczbaOtworow, double przyprostokatna)
{
    return (pow(przyprostokatna, 2) / 2) *liczbaOtworow; 
}
vector<cDane> obliczenieParametrow(double lambda, double szerokoscPlyty, double dlugoscPlyty, double maksymalnaSkutecznosc, double minimalnaSkutecznosc, double odlegloscPomiedzyOdcinkami, int polozenie, double przS, double przE)
{
    double lambdaPrzez2 = lambda / 2.0; //m
    double lambdaPrzez10 = lambda / 10.0; //m

    double szerokoscOdcinku = lambdaPrzez2; //m
    double dlugoscOdcinku = lambdaPrzez2; //m

    double przekatnaMaksymalna = przE; //m
    double przekatnaMinimalna = przS; //m

    double calkowitePoleOtworow = 0.0;

    vector <cDane> vData;
    vector <double> skut; 

    double iloscOtworowNaOdcinku = 0.0;
    double iloscOdcinkowNaPlycie = 0.0;

    double* wierszyIkolumnyOdcinek = new double[2];
    double* wierszyIkolumnyPlyta = new double[2];

    double przyprostokatna = 0.0;
    double skutecznosc = 0.0;
    vector<dodatkoweOtwory> vDataOtworyDodatkowe; 

    for (double przekatnaTymczasowa = przekatnaMaksymalna; przekatnaTymczasowa >= przekatnaMinimalna; przekatnaTymczasowa -= 0.001) //0.001 m = 1 mm
    {
        przyprostokatna = przekatnaTymczasowa / sqrt(2); // pozyskujemy dlugosc przyprostokatnej
        for (double odstepPomiedzyOtworamiWOdcinku = lambdaPrzez10; odstepPomiedzyOtworamiWOdcinku <= lambdaPrzez2; odstepPomiedzyOtworamiWOdcinku += 0.001)
        {
            wierszyIkolumnyPlyta = wierszyOrazKolumnyOdcinkowNaPlycie(szerokoscPlyty, dlugoscPlyty, odlegloscPomiedzyOdcinkami, szerokoscOdcinku, dlugoscOdcinku);
            if (polozenie == 1)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatProsty(szerokoscOdcinku, dlugoscOdcinku, odstepPomiedzyOtworamiWOdcinku, przyprostokatna);
                vDataOtworyDodatkowe= dodatkoweOtworyNaPlycie(szerokoscPlyty, dlugoscPlyty, wierszyIkolumnyPlyta, odlegloscPomiedzyOdcinkami, odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa, dlugoscOdcinku, szerokoscOdcinku, polozenie, lambda);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
            else if (polozenie == 2)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(szerokoscOdcinku, dlugoscOdcinku, odstepPomiedzyOtworamiWOdcinku, przyprostokatna);
                vDataOtworyDodatkowe = dodatkoweOtworyNaPlycie(szerokoscPlyty, dlugoscPlyty, wierszyIkolumnyPlyta, odlegloscPomiedzyOdcinkami, odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa, dlugoscOdcinku, szerokoscOdcinku, polozenie, lambda);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
            else if (polozenie == 3)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(szerokoscOdcinku, dlugoscOdcinku, odstepPomiedzyOtworamiWOdcinku, przyprostokatna, przekatnaTymczasowa);
                vDataOtworyDodatkowe = dodatkoweOtworyNaPlycie(szerokoscPlyty, dlugoscPlyty, wierszyIkolumnyPlyta, odlegloscPomiedzyOdcinkami, odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa, dlugoscOdcinku, szerokoscOdcinku, polozenie, lambda);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
            else if (polozenie == 4)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(szerokoscOdcinku, dlugoscOdcinku, odstepPomiedzyOtworamiWOdcinku, przyprostokatna, przekatnaTymczasowa);
                vDataOtworyDodatkowe = dodatkoweOtworyNaPlycie(szerokoscPlyty, dlugoscPlyty, wierszyIkolumnyPlyta, odlegloscPomiedzyOdcinkami, odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa, dlugoscOdcinku, szerokoscOdcinku, polozenie, lambda);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
           
            iloscOdcinkowNaPlycie = wierszyIkolumnyPlyta[0] * wierszyIkolumnyPlyta[1];

            skutecznosc = 20 * log10(lambda / (2 * przekatnaTymczasowa)) - 20 * log10(sqrt(wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1]));
            
            skut.push_back(skutecznosc);

            if (skutecznosc >= minimalnaSkutecznosc && skutecznosc <= maksymalnaSkutecznosc)
            {
                
                double iO = iloscOtworowNaOdcinku * iloscOdcinkowNaPlycie;
                if (!vDataOtworyDodatkowe.empty())
                    iO += (vDataOtworyDodatkowe[0].getOtworyPionoweKolumny() * vDataOtworyDodatkowe[0].getOtworyPionoweWiersze()*vDataOtworyDodatkowe[0].getIloscOdcinkowPionowe() + vDataOtworyDodatkowe[0].getOtworyPoziomeKolumny() * vDataOtworyDodatkowe[0].getOtworyPoziomeWiersze()*vDataOtworyDodatkowe[0].getIloscOdcinkowPoziome());
                cDane daneDoWektora(przekatnaTymczasowa, skutecznosc);
                daneDoWektora.setKolumny(wierszyIkolumnyPlyta[1]);
                daneDoWektora.setKolumnyOdcinek(wierszyIkolumnyOdcinek[1]);
                daneDoWektora.setOdleglosc(odstepPomiedzyOtworamiWOdcinku);
                daneDoWektora.setWierszy(wierszyIkolumnyPlyta[0]);
                daneDoWektora.setWierszyOdcinek(wierszyIkolumnyOdcinek[0]);
                calkowitePoleOtworow = poleOtworow(iO, przyprostokatna);
                daneDoWektora.setPole(calkowitePoleOtworow);
                daneDoWektora.setIloscOtwarc(iO);
                if (!vDataOtworyDodatkowe.empty())
                {
                    daneDoWektora.setDodatkoweOtworyPionK(vDataOtworyDodatkowe[0].getOtworyPionoweKolumny());
                    daneDoWektora.setDodatkoweOtworyPionW(vDataOtworyDodatkowe[0].getOtworyPionoweWiersze());
                    daneDoWektora.setDodatkoweOtworyPozK(vDataOtworyDodatkowe[0].getOtworyPoziomeKolumny());
                    daneDoWektora.setDodatkoweOtworyPozW(vDataOtworyDodatkowe[0].getOtworyPoziomeWiersze());

                    daneDoWektora.setDodatkoweOdcinkiPionowa(vDataOtworyDodatkowe[0].getIloscOdcinkowPionowe());
                    daneDoWektora.setDodatkoweOdcinkiPozioma(vDataOtworyDodatkowe[0].getIloscOdcinkowPoziome());
                }
                else
                {
                    daneDoWektora.setDodatkoweOtworyPionK(0);
                    daneDoWektora.setDodatkoweOtworyPionW(0);
                    daneDoWektora.setDodatkoweOtworyPozK(0);
                    daneDoWektora.setDodatkoweOtworyPozW(0);
                    daneDoWektora.setDodatkoweOdcinkiPionowa(0);
                    daneDoWektora.setDodatkoweOdcinkiPozioma(0);
                }
                vData.push_back(daneDoWektora);
            }

        }
    }
    ofstream out;
    out.open("ResultTxt/Skut.txt", ios::app);
    if (out.is_open())
    {
        sort(skut.begin(), skut.end(), [](const double& a, const double& b) { return a > b; });
        out << "---------------------------------------------" << endl;
        for (int i = 0; i < skut.size(); i++)
        {
            out << skut[i] << endl;
        }
    }
    return vData;
}
//------------------------------------------
int main() {
    //Program wylicza ilosc otworow, rozmiary, pole, skutecznosc i wszystkie niezbedne parametry. Po obliczeniach 
    //zapisuje wyniki do plików. Kazdy plik zawiera informacje na temat otworow, ulozonych na rozne sposoby:
    //Sposoby opisane są w sprawozdaniu i prezentacji. 
    //Dla przekatnej o rozmiarze lambda/10 nie znaleziono zadnego przykladu, wiec badana domyslnie jest przekatna minimalna o dlugosci 1 mm


    //Wartosci poczatkowe 
    double czestotliwosc = 1.56 * pow(10, 9); // Hz  //1.56
    double predkoscSwiatla = 299792458; // m/s
    double dlugoscFali = predkoscSwiatla / czestotliwosc; // m
    double szerokoscPlyty = 0.5; //m
    double dlugoscPlyty = 0.5 ; //m
    //--------------------------------------------------------------------------------------------------------------
    //Wartosci zadane
    double przekatnaMinimalna = 0.001;//dlugoscFali / 10; //m
    double przekatnaMaksymalna = dlugoscFali/2;//m
    //--------------------------------------------------------------------------------------------------------------
    double maksymalnaSkutecznosc = 100;
    double minimalnaSkutecznosc = 20.0;

    double odlegloscPomiedzyOdcinkami = dlugoscFali / 10;
    int polozenieStart=1; 
    int polozenie = 4;

    int odstepOdGranicPlyty = 0;
    int przekatnaZmiana = 0;

    //odstep od granic plyty
    //szerokoscPlyty = szerokoscPlyty - 2 * dlugoscFali / 10;
    //dlugoscPlyty = dlugoscPlyty - 2 * dlugoscFali / 10;


    int menu;
    string plik = "ResultTxt/DanePolozenie";
    string koniecPliku = ".txt";
    vector<cDane> abc; 
    do {
        cout << "Wybierz opcje: " << endl;
        cout << "1. Wpisac dane do obliczen\n2. Oblicz wartosci dla danych domyslnych\n";
        cout << "Opcja: "; cin >> menu;
        switch (menu)
        {
        case 1:
        startMenu:
            system("cls");
            cout << "1) Czestotliwosc(np. 1.5) [GHz]: "; cin >> czestotliwosc;
            cout << "2) Dlugosc plyty [m]: "; cin >> dlugoscPlyty;
            cout << "3) Szerokosc plyty [m]: "; cin >> szerokoscPlyty;
            cout << "4) Zakres skutecznosci [dB], od: "; cin >> minimalnaSkutecznosc; cout << "   do: "; cin >> maksymalnaSkutecznosc;
            cout << "5) Polozenie otworow [1-5], 5 - wszystkie mozliwosci: "; cin >> polozenie;
            cout << "6) Czy uwzglednic odstep od granic plyty? [1-2] (1 - Tak, 2 - Nie): "; cin >> odstepOdGranicPlyty;
            cout << "7) Czy zmienic rozmiar minimalnej przekatnej? [1-2] (1 - Tak, 2 - Nie): "; cin >> przekatnaZmiana;
            czestotliwosc = czestotliwosc * pow(10, 9);
            dlugoscFali = predkoscSwiatla / czestotliwosc;
            przekatnaMinimalna = dlugoscFali / 10;
            przekatnaMaksymalna = dlugoscFali / 2;
            if (przekatnaZmiana == 1)
            {
                cout << "\nMinimalna dlugosc przekatnej [m]: "; cin >> przekatnaMinimalna;
            }
            cout << "\nDane:\nPlyta[cm] :" << dlugoscPlyty << "x" << szerokoscPlyty << ", czestotliwosc[Hz]:" << czestotliwosc << ", zakres skut.: " << minimalnaSkutecznosc << " do " << minimalnaSkutecznosc
                << ", polozenie: " << polozenie;
            if (odstepOdGranicPlyty == 1)
            {
                dlugoscPlyty = dlugoscPlyty - 2 * dlugoscFali / 10;
                szerokoscPlyty = szerokoscPlyty - 2 * dlugoscFali / 10;
            }
            if (polozenie >= 5 || polozenie <= 0)
            {
                while (polozenieStart <= 4)
                {
                    plik = plik + to_string(polozenieStart) + koniecPliku;
                    abc = obliczenieParametrow(dlugoscFali, szerokoscPlyty, dlugoscPlyty, maksymalnaSkutecznosc, minimalnaSkutecznosc, odlegloscPomiedzyOdcinkami, polozenieStart, przekatnaMinimalna, przekatnaMaksymalna);
                    writeFile(abc, czestotliwosc, szerokoscPlyty, dlugoscPlyty, minimalnaSkutecznosc, maksymalnaSkutecznosc, przekatnaMinimalna, przekatnaMaksymalna, plik, polozenieStart, odlegloscPomiedzyOdcinkami);
                    polozenieStart++;
                    plik = "ResultTxt/DanePolozenie";
                }
                cout << "\nObliczenia zostaly wykonane!\n";
                return 0;
            }
            plik = plik + to_string(polozenie) + koniecPliku;
            abc = obliczenieParametrow(dlugoscFali, szerokoscPlyty, dlugoscPlyty, maksymalnaSkutecznosc, minimalnaSkutecznosc, odlegloscPomiedzyOdcinkami, polozenie, przekatnaMinimalna, przekatnaMaksymalna);
            writeFile(abc, czestotliwosc, szerokoscPlyty, dlugoscPlyty, minimalnaSkutecznosc, maksymalnaSkutecznosc, przekatnaMinimalna, przekatnaMaksymalna, plik, polozenie, odlegloscPomiedzyOdcinkami);
            polozenie++;
            plik = "ResultTxt/DanePolozenie";
            cout << "\nObliczenia zostaly wykonane!\n";
            return 0;

        case 2:
            cout << "\nDane:\nPlyta[cm] :" << dlugoscPlyty*100 << "x" << szerokoscPlyty*100 << ", czestotliwosc[Hz]:" << czestotliwosc << ", zakres skut.[dB]: " << minimalnaSkutecznosc << " do " << maksymalnaSkutecznosc
                << ", polozenie: " << 5;
            while (polozenieStart <= 4)
            {
                plik = plik + to_string(polozenieStart) + koniecPliku;
                abc = obliczenieParametrow(dlugoscFali, szerokoscPlyty, dlugoscPlyty, maksymalnaSkutecznosc, minimalnaSkutecznosc, odlegloscPomiedzyOdcinkami, polozenieStart, przekatnaMinimalna, przekatnaMaksymalna);
                writeFile(abc, czestotliwosc, szerokoscPlyty, dlugoscPlyty, minimalnaSkutecznosc, maksymalnaSkutecznosc, przekatnaMinimalna, przekatnaMaksymalna, plik, polozenieStart, odlegloscPomiedzyOdcinkami);
                polozenieStart++;
                plik = "ResultTxt/DanePolozenie";
            }
            cout << "\nObliczenia zostaly wykonane!\n";
            return 0;

        default:
            cout << "Niepoprawy wybor!";
            goto startMenu;
        }
    } while (1);
}
    