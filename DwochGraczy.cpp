#define _CRT_SECURE_NO_WARNINGS
#include "DwochGraczy.h"
#include "Dialog.h"
#include "Odpowiedz.h"
#include <iostream>
#include <cctype>

void DwochGraczy::rozmiesc() {
    Dialog::rozmieszczenie();

    //Rozmieszczenie pionkow odbywa sie 18 razy, po 9 pionkow dla kazdego z 2 graczy
    for (int i = 0; i < PNK; ++i) {
        for (int j = 1; j < 3; ++j) {
            std::cout << std::endl << "Gracz " << j << " ustala pionek: " << rodzajePionkow[i] << " (Plansza 1 lub 2)" << std::endl;

            //Ponizej zostaje okreslony gracz, plansza i rzad startowy, na ktorym beda rozkladane pionki
            //W przypadku podania zajetego pola, gracz musi powtorzyc przypisanie
            while (true) {
                int planszaNR = Odpowiedz::wyborPlanszy() - 1;
                char kolumna = Odpowiedz::wyborPola();
                int kolumnaID = toupper(kolumna) - 'A';
                int wierszID = 4;
                if (j == 2) wierszID = 0;
                if (Gra::plansza[planszaNR][wierszID][kolumnaID] == 0) {
                    Gra::plansza[planszaNR][wierszID][kolumnaID] = j * 10 + i;
                    break;
                }
                else
                    std::cout << "To pole jest juz zajete. Wybierz inne miejsce." << std::endl;
            }

            Gra::rysujPlansze(0);
            Gra::rysujPlansze(1);
        }
    }
}

void DwochGraczy::ruchGracza() {
    //Kazdy z graczy wykonuje ruch
    for (int tura = 1; tura <= 2; ++tura) {

        //Sprawdzanie dostepnosci ruchu
        if (!Gra::graczMaPionki(tura) || !Gra::graczMozeWykonacRuch(tura)) {
            std::cout << std::endl << "Gracz " << tura << " nie ma mozliwych ruchow lub pionkow. Pomijanie tury." << std::endl;
            continue;
        }

        //Wybor pionka
        std::cout << std::endl << "///////// TURA GRACZA " << tura << "/////////" << std::endl;
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
        if (wartosc / 10 != tura) {
            std::cout << "To nie jest Twoj pionek! Strata kolejki" << std::endl;
            continue;
        }

        //Ustalanie kierunku ruchu/bicia
        std::cout << "Wybierz kierunek ruchu:" << std::endl;
        Dialog::kierunek();
        int kierunek = Odpowiedz::wyborKierunku();

        int nowyWiersz = wierszID;
        int nowaKolumna = kolumnaID;

        switch (kierunek) {
        case 1:
            nowyWiersz += (tura == 1 ? -1 : 1);
            break;
        case 2:
            nowyWiersz += (tura == 1 ? -1 : 1);
            nowaKolumna -= 1;
            break;
        case 3:
            nowyWiersz += (tura == 1 ? -1 : 1);
            nowaKolumna += 1;
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
            continue;
        }

        int cel = Gra::plansza[planszaNR][nowyWiersz][nowaKolumna];

        //Jezeli pole jest rowne 0 moze zostac wykonany zwykly ruch, w przeciwnym wypadku mozna wykonac bicie
        //Zostaja tu takze naliczane punkty
        if (cel == 0) {
            if (kierunek >= 1 && kierunek <= 3) {
                Gra::plansza[planszaNR][nowyWiersz][nowaKolumna] = wartosc;
                Gra::plansza[planszaNR][wierszID][kolumnaID] = 0;
                std::cout << "Ruch wykonany." << std::endl;
                if ((tura == 1 && nowyWiersz == 0) || (tura == 2 && nowyWiersz == MAX - 1)) {
                    gracz[tura - 1].dojscieNaKoniecPlanszy();
                }
            }
            else {
                std::cout << "Nie mozna poruszyc sie na boki bez bicia!" << std::endl;
            }
        }
        else {
            int przeciwnik = cel / 10;
            if (przeciwnik != tura && Gra::moznaZbic(wartosc % 10, cel % 10)) {
                Gra::plansza[planszaNR][nowyWiersz][nowaKolumna] = wartosc;
                Gra::plansza[planszaNR][wierszID][kolumnaID] = 0;
                std::cout << "Pionek przeciwnika zbity!" << std::endl;
                gracz[tura - 1].zbiciePionka();
            }
            else {
                std::cout << "Nie mozna zbic tego pionka!" << std::endl;
            }
        }

        Gra::rysujPlansze(0);
        Gra::rysujPlansze(1);
    }
}

void DwochGraczy::rozgrywka() {
    for (int i = 0; i < 2; ++i) {
        std::cout << "GRACZ NR " << i+1 << std::endl;
        gracz[i].pytajONazwe();
    }
    rozmiesc(); //Rozstawienie pionkow przez graczy
    Dialog::rozgrywanie();
    //Gra trwa dopoki gracze maja mozliwosci ruchu
    while (true) {
        ruchGracza();

        bool gracz1aktywny = graczMaPionki(1) && graczMozeWykonacRuch(1);
        bool gracz2aktywny = graczMaPionki(2) && graczMozeWykonacRuch(2);

        if (!gracz1aktywny && !gracz2aktywny) {
            std::cout << std::endl << "Gra zakonczona - obaj gracze nie moga wykonac ruchu lub nie maja pionkow." << std::endl;
            std::cout << std::endl << "Wyniki:" << std::endl;
            for (int i = 0; i < 2; ++i) {
                std::cout << gracz[i].getNazwa() << " - " << gracz[i].getPunkty() << " punktow" << std::endl;
                Ranking::zapiszDoPliku(gracz[i]);
            }
            Ranking::wyswietlRanking();
            break;
        }
    }
}