#pragma once
#include "Gracz.h"

class Ranking {
public:
    //Dodawanie do pliku ranking.txt nowego gracza i sortowanie rankingu
    //param: gracz - uzytkownik, ktory ma byc dodany
    static void zapiszDoPliku(const Gracz& gracz);
    //Wizualizacja rankingu w konsoli
    static void wyswietlRanking();
};