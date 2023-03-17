#include "../Include/cController.h"

cController::cController(double aCzestotliwosc, double aDlugoscPlyty, double aSzerokoscPlyty, double aMinSkutecznosc, double aMaxSkutecznosc,  bool aOdstepPlyta, bool aZmianaPrzek, double aNewPrzekatna=0)
{
	czestotliwosc = aCzestotliwosc * pow(10, 9);
	dlugoscPlyty = aDlugoscPlyty;
	szerokoscPlyty = aSzerokoscPlyty;
	minimalnaSkutecznosc = aMinSkutecznosc;
	maksymalnaSkutecznosc = aMaxSkutecznosc;


	dlugoscFali = predkoscSwiatla / czestotliwosc;
	przekatnaMinimalna = dlugoscFali/10;
	przekatnaMaksymalna = dlugoscFali / 2;
     
    odstepPlyta = aOdstepPlyta;

	odlegloscPomiedzyOdcinkami = dlugoscFali / 10;
    fileName = "";

    wierszyIkolumnyOdcinek = new double[2];
    wierszyIkolumnyPlyta = new double[2];

    szerokoscOdcinku = dlugoscFali / 2;
    dlugoscOdcinku = dlugoscFali / 2;
    if (aOdstepPlyta)
    {
        szerokoscPlyty = szerokoscPlyty - dlugoscFali / 10;
        dlugoscPlyty = dlugoscPlyty - dlugoscFali / 10;
    }
    if (aZmianaPrzek)
        przekatnaMinimalna = aNewPrzekatna;
}

cController::cController()
{
	czestotliwosc = 1.56 * pow(10, 9); // Hz  //1.56
	dlugoscFali = predkoscSwiatla / czestotliwosc;
	szerokoscPlyty = 0.5;
	dlugoscPlyty = 0.5;
	przekatnaMinimalna = 0.001;
	przekatnaMaksymalna = dlugoscFali / 2;
	minimalnaSkutecznosc = 20.0;
	maksymalnaSkutecznosc = 100.0;
	odlegloscPomiedzyOdcinkami = dlugoscFali / 10;
    fileName = "";

    wierszyIkolumnyOdcinek = new double[2];
    wierszyIkolumnyPlyta = new double[2];

    szerokoscOdcinku = dlugoscFali / 2;
    dlugoscOdcinku = dlugoscFali / 2;
}
void cController::writeResultFiles()
{
    vectorSort();
    std::ofstream out;
    out.open(fileName);
    if (out.is_open())
    {
        out << "*********DANE POCATKOWE*********" << std::endl;
        out << "Czestotliwosc(Hz): " << czestotliwosc << ", rozmiar plyty(cm): " << dlugoscPlyty * 100 << "x" << szerokoscPlyty* 100 << std::endl;
        out << "Rozmiar odcinku(cm): " << (dlugoscFali / 2) * 100 << "x" << (dlugoscFali / 2) * 100 << ", odleglosc pomiedzy odc.(cm):" << odlegloscPomiedzyOdcinkami * 100 << std::endl;
        out << "Zakres skutecznosci(dB), od: " << minimalnaSkutecznosc << " do " << maksymalnaSkutecznosc<< std::endl;
        out << "Przekatna(cm), od: " << przekatnaMinimalna * 100 << " do " << przekatnaMaksymalna* 100 << std::endl;
        out << "Polozenie: " << polozenie << std::endl;
        out << "***************************************************************************" << std::endl;
        for (int i = 0; i < dataStorage.size(); i++)
        {
            out << "Liczba odcinkow na plycie: " << dataStorage[i].getWierszy() * dataStorage[i].getKolumny() << ", wierszy: " << dataStorage[i].getWierszy() << ", kolumny: " << dataStorage[i].getKolumny() << std::endl;
            out << "Odleglosc pomiêdzy odcinkami(cm): " << odlegloscPomiedzyOdcinkami * 100 << std::endl;
            out << "Liczba otworów na odcinku: " << dataStorage[i].getWierszyOdcinek() * dataStorage[i].getKolumnyOdcinek() << ", wierszy: " << dataStorage[i].getWierszyOdcinek() << ", kolumny: " << dataStorage[i].getKolumnyOdcinek() << std::endl;
            out << "Odleglosc pomiêdzy otworami(cm): " << dataStorage[i].getOdleglosc() * 100 << "; przekatna(cm): " << dataStorage[i].getPrzekatna() * 100 << std::endl;
            out << "Otrzymana skutecznosc(dB):" << dataStorage[i].getSkutecznosc() << "\nCalkowita ilosc otworow(dodatkowe): " << dataStorage[i].getIloscOtwarc() << "(" << dataStorage[i].getDodatkoweOtworyPionK() * dataStorage[i].getDodatkoweOtworyPionW() * dataStorage[i].getDodatkoweOdcinkiPionowa()
                + dataStorage[i].getDodatkoweOtworyPozK() * dataStorage[i].getDodatkoweOtworyPozW() * dataStorage[i].getDodatkoweOdcinkiPozioma() << ")" << ", ca³kowite pole otworów(cm^2): " << dataStorage[i].getPole() * 10000 << std::endl;
            out << "Dodatkowe odcinki, linia pionowa: " << dataStorage[i].getDodatkoweOdcinkiPionowa() << std::endl;
            out << "Dodatkowe otwory, odcinek linia pionowa: " << dataStorage[i].getDodatkoweOtworyPionK() * dataStorage[i].getDodatkoweOtworyPionW() << ", wierszy: " << dataStorage[i].getDodatkoweOtworyPionW() << ", kolumny: " << dataStorage[i].getDodatkoweOtworyPionK() << std::endl;
            out << "Dodatkowe odcinki, linia pozioma: " << dataStorage[i].getDodatkoweOdcinkiPozioma() << std::endl;
            out << "Dodatkowe otwory, odcinek linia pozioma: " << dataStorage[i].getDodatkoweOtworyPozK() * dataStorage[i].getDodatkoweOtworyPozW() << ", wierszy: " << dataStorage[i].getDodatkoweOtworyPozW() << ", kolumny: " << dataStorage[i].getDodatkoweOtworyPozK() << std::endl;
            out << "---------------------------------------------------------------------------" << std::endl;
        }
    }
}
void cController::vectorSort()
{
    std::sort(dataStorage.begin(), dataStorage.end(), [](cDane& a, cDane& b) -> bool
        {
            return a.getPole() > b.getPole();
        });
}

void cController::wierszyOrazKolumnyOdcinkowNaPlycie()
{
    wierszyIkolumnyPlyta[0] = floor((szerokoscPlyty) / (szerokoscOdcinku + odlegloscPomiedzyOdcinkami)); //liczba wierszy
    wierszyIkolumnyPlyta[1] = floor((dlugoscPlyty) / (dlugoscOdcinku + odlegloscPomiedzyOdcinkami)); //liczba kolumn 
}

double* cController::wierszyOrazKolumnyNaOdcinkuTrojkatProsty(double odstepPomiedzyOtworami, double przyprostokatna)
{
    double* parametryWK = new double[2];
    parametryWK[0] = floor((szerokoscOdcinku + odstepPomiedzyOtworami) / (przyprostokatna + odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = floor((dlugoscOdcinku + odstepPomiedzyOtworami) / (przyprostokatna + odstepPomiedzyOtworami)); //liczba kolumn
    return parametryWK;
}
double* cController::wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(double odstepPomiedzyOtworami, double przyprostokatna)
{
    double* parametryWK = new double[2];
    parametryWK[0] = floor((szerokoscOdcinku + odstepPomiedzyOtworami) / (przyprostokatna + odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = 2 * floor((dlugoscOdcinku + odstepPomiedzyOtworami) / (przyprostokatna + 2 * odstepPomiedzyOtworami)); //liczba kolumn
    if (parametryWK[1] / 2 * (przyprostokatna + 2 * odstepPomiedzyOtworami) + przyprostokatna <= dlugoscOdcinku)
    {
        parametryWK[1] += 1;
    }
    return parametryWK;
}
double* cController::wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(double odstepPomiedzyOtworami, double przyprostokatna, double przeciwprostokatna)
{
    double* parametryWK = new double[2];
    double wysokosc = (przyprostokatna * sqrt(2)) / 2;
    parametryWK[0] = floor((szerokoscOdcinku + odstepPomiedzyOtworami) / (wysokosc + odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = floor((dlugoscOdcinku + odstepPomiedzyOtworami) / (przeciwprostokatna + odstepPomiedzyOtworami)); //liczba kolumn
    return parametryWK;
}
double* cController::wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(double odstepPomiedzyOtworami, double przyprostokatna, double przeciwprostokatna)
{
    double* parametryWK = new double[2];
    double wysokosc = (przyprostokatna * sqrt(2)) / 2;
    parametryWK[0] = floor((szerokoscOdcinku + odstepPomiedzyOtworami) / (wysokosc + odstepPomiedzyOtworami)); //liczba wierszy
    parametryWK[1] = floor((dlugoscOdcinku + odstepPomiedzyOtworami + 2 * przeciwprostokatna) / (przeciwprostokatna + odstepPomiedzyOtworami)); //liczba kolumn
    if (int(parametryWK[1]) % 2 == 0)
    {
        parametryWK[1] -= 1;
    }
    if (((parametryWK[1] - 2) * przeciwprostokatna + parametryWK[1] * odstepPomiedzyOtworami + przeciwprostokatna / 2) <= dlugoscOdcinku)
    {
        parametryWK[1] += 1;
    }
    return parametryWK;
}
void cController::dodatkoweOtworyNaPlycie(double przekatna,double odstepOtwory)
{
    double pozostalaDlugoscPlyty = dlugoscPlyty - wierszyIkolumnyPlyta[1] * (dlugoscOdcinku+ odlegloscPomiedzyOdcinkami);
    double pozostalaSzerokoscPlyty = szerokoscPlyty - wierszyIkolumnyPlyta[0] * (szerokoscOdcinku + odlegloscPomiedzyOdcinkami);

    pozostalyOdcinekPionowyDlugosc = dlugoscFali / 2;
    double  pozostalyOdcinekPionowyDlugoscCalkowita = szerokoscPlyty - pozostalaSzerokoscPlyty;
    //
    pozostalyOdcinekPionowySzerekosc = pozostalaDlugoscPlyty;

    pozostalyOdcinekPoziomyDlugosc = dlugoscFali / 2;
    double pozostalyOdcinekPoziomyDlugoscCalkowita = dlugoscPlyty;
    //
    pozostalyOdcinekPoziomySzerekosc = pozostalaSzerokoscPlyty;

    double* dodatkoweOtworyPionowe = new double[2]; //odcinek Pionowy
    double* dodatkoweOtworyPoziome = new double[2]; //odcinek Poziomy

    double przyprostokatna = przekatna / sqrt(2);

    double iloscOdcinkowPionowa = floor((pozostalyOdcinekPionowyDlugoscCalkowita) / (pozostalyOdcinekPionowyDlugosc + dlugoscFali / 10));
    double iloscOdcinkowPozioma = floor((pozostalyOdcinekPoziomyDlugoscCalkowita) / (pozostalyOdcinekPoziomyDlugosc + dlugoscFali / 10));

    if (polozenie == 1)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatProsty(odstepOtwory, przyprostokatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatProsty(odstepOtwory, przyprostokatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        v_dodatkoweOtwory.push_back(dodatkoweOtworyTemp);
    }
    else if (polozenie == 2)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(odstepOtwory, przyprostokatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(odstepOtwory, przyprostokatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        v_dodatkoweOtwory.push_back(dodatkoweOtworyTemp);
    }
    else if (polozenie == 3)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        v_dodatkoweOtwory.push_back(dodatkoweOtworyTemp);
    }
    else if (polozenie == 4)
    {
        dodatkoweOtworyPionowe = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtworyPoziome = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(odstepOtwory, przyprostokatna, przekatna);
        dodatkoweOtwory dodatkoweOtworyTemp(dodatkoweOtworyPionowe[0], dodatkoweOtworyPionowe[1], dodatkoweOtworyPoziome[0], dodatkoweOtworyPoziome[1], iloscOdcinkowPionowa, iloscOdcinkowPozioma);
        v_dodatkoweOtwory.push_back(dodatkoweOtworyTemp);
    }
}
double cController::poleOtworow(double liczbaOtworow, double przyprostokatna)
{
    return (pow(przyprostokatna, 2) / 2) * liczbaOtworow;
}
void cController::obliczenieParametrow()
{
    double lambdaPrzez2 = dlugoscFali / 2.0; //m
    double lambdaPrzez10 = dlugoscFali / 10.0; //m

    double szerokoscOdcinku = lambdaPrzez2; //m
    double dlugoscOdcinku = lambdaPrzez2; //m


    std::vector <double> v_skutecznosc;

    double iloscOtworowNaOdcinku = 0.0;
    double iloscOdcinkowNaPlycie = 0.0;

    //double* wierszyIkolumnyOdcinek = new double[2];
    //double* wierszyIkolumnyPlyta = new double[2];

    double przyprostokatna = 0.0;
    double skutecznosc = 0.0;

    for (double przekatnaTymczasowa = przekatnaMaksymalna; przekatnaTymczasowa >= przekatnaMinimalna; przekatnaTymczasowa -= 0.001) //0.001 m = 1 mm
    {
        przyprostokatna = przekatnaTymczasowa / sqrt(2); // pozyskujemy dlugosc przyprostokatnej
        for (double odstepPomiedzyOtworamiWOdcinku = lambdaPrzez10; odstepPomiedzyOtworamiWOdcinku <= lambdaPrzez2; odstepPomiedzyOtworamiWOdcinku += 0.001)
        {
            wierszyOrazKolumnyOdcinkowNaPlycie();
            if (polozenie == 1)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatProsty(odstepPomiedzyOtworamiWOdcinku, przyprostokatna);
                dodatkoweOtworyNaPlycie(odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
            else if (polozenie == 2)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciKwadratu(odstepPomiedzyOtworamiWOdcinku, przyprostokatna);
                dodatkoweOtworyNaPlycie( odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
            else if (polozenie == 3)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciNaPrzeciwprosokatnej(odstepPomiedzyOtworamiWOdcinku, przyprostokatna, przekatnaTymczasowa);
                dodatkoweOtworyNaPlycie(odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
            else if (polozenie == 4)
            {
                wierszyIkolumnyOdcinek = wierszyOrazKolumnyNaOdcinkuTrojkatWPostaciZebow(odstepPomiedzyOtworamiWOdcinku, przyprostokatna, przekatnaTymczasowa);
                dodatkoweOtworyNaPlycie(odstepPomiedzyOtworamiWOdcinku, przekatnaTymczasowa);
                iloscOtworowNaOdcinku = wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1];
            }
            iloscOdcinkowNaPlycie = wierszyIkolumnyPlyta[0] * wierszyIkolumnyPlyta[1];
            skutecznosc = 20 * log10(dlugoscFali / (2 * przekatnaTymczasowa)) - 20 * log10(sqrt(wierszyIkolumnyOdcinek[0] * wierszyIkolumnyOdcinek[1]));
            v_skutecznosc.push_back(skutecznosc);
            if (skutecznosc >= minimalnaSkutecznosc && skutecznosc <= maksymalnaSkutecznosc)
            {
                double iO = iloscOtworowNaOdcinku * iloscOdcinkowNaPlycie;
                if (!v_dodatkoweOtwory.empty())
                    iO += (v_dodatkoweOtwory[0].getOtworyPionoweKolumny() * v_dodatkoweOtwory[0].getOtworyPionoweWiersze() * v_dodatkoweOtwory[0].getIloscOdcinkowPionowe() 
                        + v_dodatkoweOtwory[0].getOtworyPoziomeKolumny() * v_dodatkoweOtwory[0].getOtworyPoziomeWiersze() * v_dodatkoweOtwory[0].getIloscOdcinkowPoziome());
                addData(przekatnaTymczasowa, skutecznosc, odstepPomiedzyOtworamiWOdcinku, przyprostokatna, iO);                
            }
            v_dodatkoweOtwory.clear();
        }
    }
}
void cController::addData(double aPrzekatnaTymczasowa, double aSkutecznosc, double aOdstepPomiedzyOtworamiWOdcinku, double aPrzyprostokatna, double aLiczbaOtworow)
{
    cDane daneDoWektora(aPrzekatnaTymczasowa, aSkutecznosc);
    daneDoWektora.setKolumny(wierszyIkolumnyPlyta[1]);
    daneDoWektora.setKolumnyOdcinek(wierszyIkolumnyOdcinek[1]);
    daneDoWektora.setOdleglosc(aOdstepPomiedzyOtworamiWOdcinku);
    daneDoWektora.setWierszy(wierszyIkolumnyPlyta[0]);
    daneDoWektora.setWierszyOdcinek(wierszyIkolumnyOdcinek[0]);
    daneDoWektora.setPole(poleOtworow(aLiczbaOtworow, aPrzyprostokatna));
    daneDoWektora.setIloscOtwarc(aLiczbaOtworow);
    if (!v_dodatkoweOtwory.empty())
    {
        daneDoWektora.setDodatkoweOtworyPionK(v_dodatkoweOtwory[0].getOtworyPionoweKolumny());
        daneDoWektora.setDodatkoweOtworyPionW(v_dodatkoweOtwory[0].getOtworyPionoweWiersze());
        daneDoWektora.setDodatkoweOtworyPozK(v_dodatkoweOtwory[0].getOtworyPoziomeKolumny());
        daneDoWektora.setDodatkoweOtworyPozW(v_dodatkoweOtwory[0].getOtworyPoziomeWiersze());

        daneDoWektora.setDodatkoweOdcinkiPionowa(v_dodatkoweOtwory[0].getIloscOdcinkowPionowe());
        daneDoWektora.setDodatkoweOdcinkiPozioma(v_dodatkoweOtwory[0].getIloscOdcinkowPoziome());
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
    dataStorage.push_back(daneDoWektora);
}
void cController::printData()
{

    std::cout << "\nDane:\nPlyta[cm] :" << dlugoscPlyty * 100 << "x" << szerokoscPlyty * 100 << ", czestotliwosc[Hz]:" << czestotliwosc << ", zakres skut.[dB]: " << minimalnaSkutecznosc << " do " << maksymalnaSkutecznosc
        << ", polozenie: " << 5 << std::endl;
    std::cout << "Min.Przekatna[cm]: " << przekatnaMinimalna * 100 << ", max.Przekatna[cm]: " << przekatnaMaksymalna * 100;
}
void cController::createFileName(std::string temp)
{
    fileName = plik + temp + koniecPliku;
}
void cController::startCalculation(int aPolozenie)
{
    polozenie = aPolozenie;
    createFileName(std::to_string(aPolozenie));
    obliczenieParametrow();
    writeResultFiles();
    fileName = "";
    dataStorage.clear();
    v_dodatkoweOtwory.clear();
}

