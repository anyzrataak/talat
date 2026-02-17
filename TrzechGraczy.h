#pragma once
#include "Gra.h"
#include "Gracz.h"
#include "Ranking.h"

class TrzechGraczy : public Gra {
private:
    //Tablica trzech graczy bioracych udzial w grze
    Gracz gracz[3];
    //Okresla kierunek ruchu pionkow gracza wedlug planszy, na ktorej sie znajduje
    //param: gracz - nr gracza potrzebny do okreslenia kierunku ruchu [1, 3]
    //param: planszaNR: nr planszy potrzebny do okreslenia kierunku ruchu [0, 2]
    //return: -1 - porusza sie do gory
    //return: 1 - porusza sie do dolu
    int kierunekRuchu(int gracz, int planszaNR);
    //Okresla numer planszy wedlug wpisywanych przez uzytkownika danych w konsoli
    //param: gracz - nr gracza potrzebny do okreslenia nr planszy [1, 3]
    //param: wybor - wybor planszy przez uzytkownika [1, 3]
    //return: 0 - gracz nr 1 wybral pierwsza plansze albo gracz nr 3 wybral druga plansze
    //return: 1 - gracz nr 2 wybral pierwsza plansze albo gracz nr 1 wybral druga plansze
    //return: 2 - gracz nr 3 wybral pierwsza plansze albo gracz nr 2 wybral druga plansze
    int mapujPlansze(int gracz, int wybor);
    //Rozmieszcza na zmiane po 9 pionkow kazdego z trzech graczy wedlug wpisywanych przez nich danych do konsoli
    void rozmiesc();
    //Przejscie jednej tury, w ktorej kazdy z graczy ma do wyboru jeden ruch dowolnie wybranym przez siebie pionkiem, ktory jest aktywny, poprawnosc ruchu jest sprawdzana
    void ruchGracza();
    //Sprawdzanie, czy gracz posiada jakiekolwiek pionki
    //param: gracz - nr sprawdzanego gracza
    //return: true - posiada
    //return: false - nie posiada
    bool graczMaPionki3(int gracz);
    //Sprawdzenie, czy gracz moze wykonac jakikolwiek ruch ktorymkolwiek ze swoich pionkow
    //param: gracz - nr sprawdzanego gracza
    //return: true - moze
    //return: false - nie moze
    bool graczMozeWykonacRuch3(int gracz);
public:
    //Przebieg wszystkich tur, podsumowanie gry i wyswietlenie rankingu
    void rozgrywka() override;
};