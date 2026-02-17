#define _CRT_SECURE_NO_WARNINGS
#include "JedenGracz.h"
#include "Dialog.h"
#include "Odpowiedz.h"
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <windows.h>
#include <iostream>

void JedenGracz::rozmiesc() {
    Dialog::rozmieszczenie();
    srand(time(NULL));

    //Ponizsze zmienne pomagaja w rozroznianiu pionkow
    int graczID = 1;
    int komputerID = 2;

    //Rozmieszczenie pionkow odbywa sie 18 razy, po 9 pionkow dla gracza i komputera
    for (int i = 0; i < PNK; ++i) {
        std::cout << std::endl << "Gracz ustala pionek: " << rodzajePionkow[i] << std::endl;

        //Ponizej zostaje okreslony gracz, plansza i rzad startowy, na ktorym beda rozkladane pionki
        //W przypadku podania zajetego pola, gracz musi powtorzyc przypisanie
        while (true) {
            int planszaNR = Odpowiedz::wyborPlanszy() - 1;
            char kolumna = Odpowiedz::wyborPola();
            int kolumnaID = toupper(kolumna) - 'A';
            if (Gra::plansza[planszaNR][4][kolumnaID] == 0) {
                Gra::plansza[planszaNR][4][kolumnaID] = graczID * 10 + i;
                break;
            }
            else
                std::cout << "To pole jest juz zajete. Wybierz inne miejsce." << std::endl;
        }

        Sleep(1000);
        std::cout << "Komputer ustawia pionek: " << rodzajePionkow[i] << std::endl;
        bool ustawiono = false; //Zmienna sprawdza, czy dostepne jest pole na planszy wylosowane przez komputer

        //Losowane jest pole do momentu wyboru pustego miejsca
        while (!ustawiono) {
            int randPlansza = rand() % 2;
            int randKolumna = rand() % 5;
            int komputerWiersz = 0;

            if (Gra::plansza[randPlansza][komputerWiersz][randKolumna] == 0) {
                Gra::plansza[randPlansza][komputerWiersz][randKolumna] = komputerID * 10 + i;
                ustawiono = true;
            }
        }

        Gra::rysujPlansze(0);
        Gra::rysujPlansze(1);
    }
}

void JedenGracz::ruchGracza() {
    //Sprawdzanie dostepnosci ruchu
    if (!Gra::graczMaPionki(1) || !Gra::graczMozeWykonacRuch(1)) {
        std::cout << std::endl << "Gracz nie ma mozliwych ruchow lub pionkow.Komputer konczy swoje tury" << std::endl;
        return;
    }

    //Wybor pionka
    std::cout << std::endl << "///////// TURA GRACZA /////////" << std::endl;
    std::cout << "Wybierz plansze (1 lub 2)" << std::endl;
    int planszaNR = Odpowiedz::wyborPlanszy() - 1;
    std::cout << "Wybierz kolumne pionka (A, B, C ,D, E):" << std::endl;
    char kolumna = Odpowiedz::wyborPola();
    std::cout << "Wybierz wiersz pionka [1, 5]:" << std::endl;
    int wiersz = Odpowiedz::wyborWiersza();

    int kolumnaID = toupper(kolumna) - 'A';
    int wierszID = wiersz - 1;

    int wartosc = Gra::plansza[planszaNR][wierszID][kolumnaID];

    //Sprawdzanie, czy dane uzytkownika pokrywaja sie z pionkiem znajdujacym sie na danym polu (czy nalezy do niego)
    if (wartosc / 10 != 1) {
        std::cout << "To nie jest Twoj pionek! Strata kolejki" << std::endl;
        return;
    }

    //Ustalanie kierunku ruchu/bicia
    std::cout << "Wybierz kierunek ruchu:" << std::endl;
    Dialog::kierunek();
    int kierunek = Odpowiedz::wyborKierunku();

    int nowyWiersz = wierszID;
    int nowaKolumna = kolumnaID;

    switch (kierunek) {
    case 1:
        nowyWiersz -= 1;
        break;
    case 2: 
        nowyWiersz -= 1; nowaKolumna -= 1;
        break;
    case 3:
        nowyWiersz -= 1; nowaKolumna += 1; 
        break;
    case 4: 
        nowaKolumna -= 1; 
        break;
    case 5: 
        nowaKolumna += 1;
        break;
    }

    if (nowyWiersz < 0 || nowyWiersz >= MAX || nowaKolumna < 0 || nowaKolumna >= MAX) {
        std::cout << "Nieprawidlowy ruch! Poza plansza." << std::endl;
        return;
    }

    int cel = Gra::plansza[planszaNR][nowyWiersz][nowaKolumna];

    //Jezeli pole jest rowne 0 moze zostac wykonany zwykly ruch, w przeciwnym wypadku mozna wykonac bicie
    //Zostaja tu takze naliczane punkty
    if (cel == 0) {
        if (kierunek >= 1 && kierunek <= 3) {
            Gra::plansza[planszaNR][nowyWiersz][nowaKolumna] = wartosc;
            Gra::plansza[planszaNR][wierszID][kolumnaID] = 0;
            std::cout << "Ruch wykonany." << std::endl;
            if (nowyWiersz == 0) {
                gracz.dojscieNaKoniecPlanszy();
            }
        }
        else {
            std::cout << "Nie mozna poruszyc sie na boki bez bicia!" << std::endl;
        }
    }
    else {
        int przeciwnik = cel / 10;
        if (przeciwnik == 2 && Gra::moznaZbic(wartosc % 10, cel % 10)) {
            Gra::plansza[planszaNR][nowyWiersz][nowaKolumna] = wartosc;
            Gra::plansza[planszaNR][wierszID][kolumnaID] = 0;
            std::cout << "Pionek przeciwnika zbity!" << std::endl;
            gracz.zbiciePionka();
        }
        else {
            std::cout << "Nie mozna zbic tego pionka!" << std::endl;
        }
    }

    Gra::rysujPlansze(0);
    Gra::rysujPlansze(1);
}

void JedenGracz::ruchKomputera() {
    //Przechoduje informacje o mozliwym ruchu
    struct Ruch {
        int plansza, x, y; //Nr planszy danego pionka i jego wspolrzedne
        int dx, dy; //ruch w pionie i w poziomie
    };

    const int MAX_RUCHOW = 100;
    Ruch mozliweRuchy[MAX_RUCHOW];
    int liczbaRuchow = 0;

    srand((unsigned int)time(NULL));

    //Pzeszukuje wszystkie pol na obu planszach
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < MAX; ++j) {
            for (int k = 0; k < MAX; ++k) {
                int wartosc = Gra::plansza[i][j][k];

                //Sprawdza tylko pionki nalezace do komputera
                if (wartosc / 10 != 2)
                    continue;

                int pionekID = wartosc % 10; //Rozpoznaje pionek po jego wartosci

                //Definicja mozliwych kierunkow ruchu (w dol)
                const int kierunkiKomputer[5][2] = { {1, 0}, {1, -1}, {1, 1}, {0, -1}, {0, 1} };

                for (int l = 0; l < 5; ++l) {
                    int nowyWiersz = j + kierunkiKomputer[l][0]; //Nowy wiersz
                    int nowaKolumna = k + kierunkiKomputer[l][1]; //Nowa kolumna

                    if (nowyWiersz < 0 || nowyWiersz >= MAX || nowaKolumna < 0 || nowaKolumna >= MAX)
                        continue;

                    int cel = Gra::plansza[i][nowyWiersz][nowaKolumna];

                    //Ruch bez bicia
                    if (cel == 0 && kierunkiKomputer[l][0] != 0) {
                        if (liczbaRuchow < MAX_RUCHOW) {
                            mozliweRuchy[liczbaRuchow++] = { i, j, k, kierunkiKomputer[l][0], kierunkiKomputer[l][1] };
                        }
                    }

                    //Ruch z biciem
                    if (cel != 0 && cel / 10 == 1 && Gra::moznaZbic(pionekID, cel % 10)) {
                        if (liczbaRuchow < MAX_RUCHOW) {
                            mozliweRuchy[liczbaRuchow++] = { i, j, k, kierunkiKomputer[l][0], kierunkiKomputer[l][1] };
                        }
                    }
                }
            }
        }
    }

    if (liczbaRuchow == 0) {
        std::cout << "Komputer nie ma mozliwych ruchow." << std::endl;
        return;
    }

    //Losowy wybor jednego z mozliwych ruchow
    Ruch r = mozliweRuchy[rand() % liczbaRuchow];

    //Referencje do pol w planszy, umozliwiaja szybszy dostep
    int& przed = Gra::plansza[r.plansza][r.x][r.y];
    int& po = Gra::plansza[r.plansza][r.x + r.dx][r.y + r.dy];

    if (po != 0) {
        std::cout << "Komputer zbija pionek gracza!" << std::endl;
    }
    else {
        std::cout << "Komputer wykonuje ruch." << std::endl;
    }

    po = przed; //Przenoszenie pionka na nowe miejsce
    przed = 0; //Usuwanie starego pionka

    Gra::rysujPlansze(0);
    Gra::rysujPlansze(1);
}

void JedenGracz::rozgrywka() {
    gracz.pytajONazwe();
    rozmiesc(); //Rozstawienie pionkow przez gracza i komputer
    Dialog::rozgrywanie();
    //Gra trwa dopoki gracz i komputer maja mozliwosci ruchu
    while (Gra::graczMaPionki(1) && Gra::graczMaPionki(2) &&
        (Gra::graczMozeWykonacRuch(1) || Gra::graczMozeWykonacRuch(2))) {

        //Tura gracza
        if (Gra::graczMozeWykonacRuch(1)) {
            ruchGracza();
        }
        else {
            std::cout << std::endl << "Gracz nie moze wykonac ruchu." << std::endl;
        }

        //Tura komputera
        if (Gra::graczMozeWykonacRuch(2)) {
            Sleep(2000);
            std::cout << std::endl << "///////// TURA KOMPUTERA /////////" << std::endl;
            ruchKomputera();
        }
        else {
            std::cout << std::endl << "Komputer nie moze wykonac ruchu." << std::endl;
        }
    }

    std::cout << std::endl << "Gra zakonczona!" << std::endl;
    std::cout << std::endl << "Twoj wynik: " << gracz.getNazwa() << " - " << gracz.getPunkty() << " punktow" << std::endl;
    Ranking::zapiszDoPliku(gracz);
    Ranking::wyswietlRanking();
}