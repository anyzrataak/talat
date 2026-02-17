#pragma once

#define MAX_NAZWA 30

class Gracz {
private:
    //Nazwa gracza
    //Format: [MAX_NAZWA], gdzie:
    //MAX_NAZWA to maksymalna dlugosc nazwy gracza - 30
    char nazwa[MAX_NAZWA];
    int punkty; //Punkty danego gracza
public:
    //Konstruktor domyslny tworzacy nowego gracza oraz zerujacy mu punkty
    Gracz();
    //Pobieranie nazwy uzytkownika
    void pytajONazwe();
    //Doliczanie 5 punktow za zbicie pionka
    void zbiciePionka();
    //Doliczanie 3 punktow za dojscie do konca planszy
    void dojscieNaKoniecPlanszy();
    //Zwraca nazwe gracza
    //return: nazwa - wskaznik do pierwszego elementu lancucha reprezentujacego nazwe uzytkownika
    const char* getNazwa() const;
    //Zwraca ilosc punktow
    //return: punkty
    int getPunkty() const;
};