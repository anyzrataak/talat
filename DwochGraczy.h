#pragma once
#include "Gra.h"
#include "Gracz.h"
#include "Ranking.h"

class DwochGraczy : public Gra {
private:
    //Tablica dwoch graczy bioracych udzial w grze
    Gracz gracz[2];
    //Rozmieszcza na zmiane po 9 pionkow kazdego z dwoch graczy wedlug wpisywanych przez nich danych do konsoli
    void rozmiesc();
    //Przejscie jednej tury, w ktorej kazdy z graczy ma do wyboru jeden ruch dowolnie wybranym przez siebie pionkiem, ktory jest aktywny, poprawnosc ruchu jest sprawdzana
    void ruchGracza();
public:
    //Przebieg wszystkich tur, podsumowanie gry i wyswietlenie rankingu
    void rozgrywka() override;
};