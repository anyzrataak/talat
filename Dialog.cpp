#define _CRT_SECURE_NO_WARNINGS
#include "Dialog.h"
#include <windows.h>
#include <iostream>
#include <cstring>

int Dialog::pobieranieSzerokosci() {
    CONSOLE_SCREEN_BUFFER_INFO csbi; //Pobieranie informacji o konsoli
    int szerokosc = 80; //Ustawianie domyslnej szerokosci, gdyby pobranie faktycznej szerokosci konsoli nie powiodlo sie
    //Jezeli pobieranie informacji powiodlo sie, szerokosc zostaje ustalona zgodnie z nimi
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        szerokosc = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return szerokosc;
}

void Dialog::wysrodkowanieTekstu(const char tekst[]) {
    int spacje = (pobieranieSzerokosci() - strlen(tekst)) / 2; //Ustalanie odstepu od lewej krawedzi konsoli
    if (spacje < 0) spacje = 0;
    for (int i = 0; i < spacje; ++i) putchar(' ');
    std::cout << tekst << std::endl;
}

//Ponizsze cztery metody korzystaja z metody wysrodkowanieTekstu w celu wyswietlenia go na srodku ekranu

void Dialog::powitanie() {
    wysrodkowanieTekstu("GRA TALAT\n");
    wysrodkowanieTekstu("Projekt semestralny - Programowanie obiektowe 2025");
    wysrodkowanieTekstu("Autorka: Katarzyna Piatek, nr albumu: 130282\n\n");
}

void Dialog::trybRozgrywki() {
    std::cout << std::endl << std::endl;
    wysrodkowanieTekstu("Do wyboru sa dwa tryby gry");
    wysrodkowanieTekstu("Gra z wirtualnym przeciwnikiem - wcisnij 1");
    wysrodkowanieTekstu("Gra wieloosobowa - wcisnij 2 lub 3 (w zaleznosci od ilosci graczy)");
}

void Dialog::zasady() {
    std::cout << std::endl << std::endl;
    wysrodkowanieTekstu("Zasady gry TALAT:");
    wysrodkowanieTekstu("1. Celem gry jest zbijanie pionow przeciwnika i dotarcie do jego linii startowej.");
    wysrodkowanieTekstu("2. Gra odbywa sie na trzech planszach 5x5.");
    wysrodkowanieTekstu("3. Kazdy gracz ma 9 pionow w trzech ksztaltach i trzech rozmiarach.");
    wysrodkowanieTekstu("4. Piony poruszaja sie do przodu o jedno pole, wprost lub na ukos.");
    wysrodkowanieTekstu("5. Piony moga bic inne, ktore sa mniejsze o jedno oczko lub o mniejsza liczbe bokow.");
    wysrodkowanieTekstu("6. Najmniejszy trojkat moze pobic najwiekszy szesciobok.");
    wysrodkowanieTekstu("7. Gra konczy sie, gdy obie plansze zostana zamrozone.");
    wysrodkowanieTekstu("8. Punkty: 5 za zbitego pionka przeciwnika, 3 za pionka, ktory dotarl na linie startowa.");
}

void Dialog::wyswietlanieRankingu() {
    std::cout << std::endl << std::endl << std::endl;
    wysrodkowanieTekstu("//////////////////////////////////////////////////////////////////////////////////////////////////////");
    wysrodkowanieTekstu("R A N K I N G");
}

//Ponizsze metody wyswietlaja powtarzajace sie w roznych trybach zlozone komunikaty

void Dialog::rozmieszczenie() {
    std::cout << std::endl << std::endl << "PIERWSZY ETAP - ROZMIESZCZENIE PIONKOW" << std::endl;
    std::cout << "Na zmiane kazdy z graczy (lub gracz i komputer) umieszczaja 9 pionkow na dwoch planszach" << std::endl;
    std::cout << "Prosze o podanie numeru planszy (1 lub 2)" << std::endl;
    std::cout << "Nastepnie o podanie numeru pozycji pionka [A-E]" << std::endl << std::endl;
}

void Dialog::rozgrywanie() {
    std::cout << std::endl << "DRUGI ETAP - GRA" << std::endl;
    std::cout << "Na zmiane kazdy z graczy (lub gracz i komputer) wykonuja ruch" << std::endl;
    std::cout << "Mozliwe ruchy to do przodu i na ukos o jedno pole (bicie dodatkowo na boki)" << std::endl;
    std::cout << "Dla uproszczenia nazwy pionow na planszy sa numerami od 0 do 8" << std::endl;
    std::cout << "Bicie odbywa sie wg schematu:" << std::endl;
    std::cout << "0 bije 8" << std::endl;
    std::cout << "1 bije 0" << std::endl;
    std::cout << "2 bije 1" << std::endl;
    std::cout << "3 bije 2, 1, 0" << std::endl;
    std::cout << "4 bije 3, 2, 1, 0" << std::endl;
    std::cout << "5 bije 4, 2, 1, 0" << std::endl;
    std::cout << "6 bije 5, 4, 3" << std::endl;
    std::cout << "7 bije 6, 5, 4, 3" << std::endl;
    std::cout << "8 bije 7, 5, 4, 3" << std::endl;
    std::cout << "Gra konczy sie, gdy nie bedzie mozliwosci wykonania ruchu przez graczy" << std::endl;
}

void Dialog::kierunek() {
    std::cout << "1: na wprost" << std::endl;
    std::cout << "2: ukosnie w lewo" << std::endl;
    std::cout << "3: ukosnie w prawo" << std::endl;
    std::cout << "4: w lewo (bicie)" << std::endl;
    std::cout << "5: w prawo (bicie)" << std::endl;
}