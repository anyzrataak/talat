#pragma once
#include "Gra.h"
#include "Gracz.h"
#include "Ranking.h"

class JedenGracz : public Gra {
private:
    //Gracz bioracy udzial w grze
    Gracz gracz;
    //Rozmieszcza na zmiane po 9 pionkow gracza i komputera wedlug wpisywanych przez uzytkownika danych do konsoli i losowych parametrow generowanych dla komputera
    void rozmiesc();
    //Przejscie jednej tury, w ktorej gracz ma do wyboru jeden ruch dowolnie wybranym przez siebie pionkiem, ktory jest aktywny, poprawnosc ruchu jest sprawdzana
    void ruchGracza();
    //Wykonanie przez komputer losowego ruchu pionka zgodnie z przyjetymi zasadami gry i mozliwosciami na planszy
    void ruchKomputera();
public:
    //Przebieg wszystkich tur, podsumowanie gry i wyswietlenie rankingu
    void rozgrywka() override;
};