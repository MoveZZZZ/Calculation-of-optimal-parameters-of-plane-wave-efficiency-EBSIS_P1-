#include"../Include/cMenu.h"

cMenu::cMenu()
{
    bOdstepOdGranic = false;
    bPrzekatnaZmiana = false;
    polozenie = 5;
    polozenieStart = 1;
}


void cMenu::printMenu()
{
    do {
    startMenu:
        std::cout << "+---------------------------------------------------+\n";
        std::cout << "|             Author: Maksim Filatau                |\n";
        std::cout << "|             Indeks: 259156                        |\n";
        std::cout << "|***************************************************|\n";
        std::cout << "|     Program sluzy do obliczenia optymalnej        |\n";
        std::cout << "|           liczby n - otworow, S - pola            |\n";
        std::cout << "|            dla znanej czestotliwosci              |\n";
        std::cout << "|            i podanego rozmiaru plyty              |\n";
        std::cout << "|          w znanym zakresie skutecznosci           |\n";
        std::cout << "|          dla roznie ulozonych trojkatow           |\n";
        std::cout << "|           prostokatnych rownoramiennych           |\n";
        std::cout << "|***************************************************|\n";
        std::cout << "|                 Wybierz opcje                     |\n";
        std::cout << "|+++++++++++++++++++++++++++++++++++++++++++++++++++|\n";
        std::cout << "| 1: Wpisac wlasne dane do obliczen                 |\n";
        std::cout << "| 2: Obliczyc wartosci wedlug danych domyslnych     |\n";
        std::cout << "+---------------------------------------------------+\n";
        std::cout << "Opcja: "; std::cin >> menu;
        switch (menu)
        {
        case 1:
            printCase1();
        case 2:
            printCase2();
        default:
            std::cout << "Niepoprawy wybor!";
            goto startMenu;
        }
    } while (1);
}

void cMenu::printCase1()
{
    system("cls");
    std::cout << "1) Czestotliwosc(np. 1.5) [GHz]: "; std::cin >> czestotliwosc;
    std::cout << "2) Dlugosc plyty [m]: "; std::cin >> dlugoscPlyty;
    std::cout << "3) Szerokosc plyty [m]: "; std::cin >> szerokoscPlyty;
    std::cout << "4) Zakres skutecznosci [dB], od: "; std::cin >> minimalnaSkutecznosc; std::cout << "   do: "; std::cin >> maksymalnaSkutecznosc;
    std::cout << "5) Polozenie otworow [1-5], 5 - wszystkie mozliwosci: "; std::cin >> polozenie;
    std::cout << "6) Czy uwzglednic odstep od granic plyty? [1-2] (1 - Tak, 2 - Nie): "; std::cin >> odstepOdGranic;
    std::cout << "7) Czy zmienic rozmiar minimalnej przekatnej? [1-2] (1 - Tak, 2 - Nie): "; std::cin >> przekatnaZmiana;
    if (przekatnaZmiana == 1)
    {
        bPrzekatnaZmiana = true;
        std::cout << "Minimalna dlugosc przekatnej [m]: "; std::cin >> przekatnaMinimalna;
    }
    if (odstepOdGranic == 1)
    {
        bOdstepOdGranic = true;
    }
    cController* controller;
    controller = new cController(czestotliwosc, dlugoscPlyty, szerokoscPlyty, minimalnaSkutecznosc, maksymalnaSkutecznosc, bOdstepOdGranic, bPrzekatnaZmiana, przekatnaMinimalna);
    //cController controller(czestotliwosc, dlugoscPlyty, szerokoscPlyty, minimalnaSkutecznosc, maksymalnaSkutecznosc, bOdstepOdGranic, bPrzekatnaZmiana, przekatnaMinimalna);
    controller->printData();
    if (polozenie >= 5 || polozenie <= 0)
    {
        while (polozenieStart <= 4)
        {
            controller->startCalculation(polozenieStart);
            polozenieStart++;
        }
        std::cout << "\nObliczenia zostaly wykonane!\n";
        exit(1);
    }
    controller->startCalculation(polozenie);
    std::cout << "\nObliczenia zostaly wykonane!\n";
    exit(1);
}

void cMenu::printCase2()
{
    cController *controller;
    controller = new cController();
    controller->printData();
    while (polozenieStart <= 4)
    {
        controller->startCalculation(polozenieStart);
        polozenieStart++;
    }
    std::cout << "\nObliczenia zostaly wykonane!\n";
    delete controller;
    exit(1);
}
