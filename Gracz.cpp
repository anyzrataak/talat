#define _CRT_SECURE_NO_WARNINGS
#include "Gracz.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

//Ustawienie domyslnej nazwy gracza i zerowanie punktow na start
Gracz::Gracz() : nazwa("Gracz1"), punkty(0) {}

void Gracz::pytajONazwe() {
    std::cout << "Podaj nazwe gracza: " << std::endl;
    std::cin >> nazwa;
}

void Gracz::zbiciePionka() {
    //Doliczenie 5 punktow za zbicie pionka
    punkty += 5;
}

void Gracz::dojscieNaKoniecPlanszy() {
    //Doliczenie 3 punktow za przejscie na koniec planszy
    punkty += 3;
}

const char* Gracz::getNazwa() const {
    //Zwracanie wskaznika do lancucha reprezentujacego nazwe gracza
    return nazwa;
}

int Gracz::getPunkty() const {
    //Zwracanie ilosci punktow gracza
    return punkty;
}