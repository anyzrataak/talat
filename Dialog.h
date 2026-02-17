#pragma once

class Dialog {
private:
    //Pobiera szerokosc konsoli
    //return: szerokosc
    static int pobieranieSzerokosci();
    //Wyswietla tekst na srodku konsoli
    //param: tekst
    static void wysrodkowanieTekstu(const char tekst[]);
public:
    //Wyswietla na srodku konsoli informacje o autorze i projekcie
    static void powitanie();
    //Wyswietla na srodku konsoli informacje o mozliwych trybach rozgrywki
    static void trybRozgrywki();
    //Wyswietla na srodku konsoli zasady gry
    static void zasady();
    //Wyswietla na srodku konsoli naglowek rankingu
    static void wyswietlanieRankingu();
    //Informuje o mozliwych opcjach rozmieszczenia pionkow
    static void rozmieszczenie();
    //Przypomina zasady gry i uproszczone oznaczenia pionkow na planszy
    static void rozgrywanie();
    //Wyswietla informacje o mozliwych kierunkach gry za kazdym razem, gdy pionek ma wykonac ruch
    static void kierunek();
};