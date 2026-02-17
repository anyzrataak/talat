#define _CRT_SECURE_NO_WARNINGS
#include "TrzechGraczy.h"
#include "Dialog.h"
#include "Odpowiedz.h"
#include <iostream>
#include <cctype>

int TrzechGraczy::kierunekRuchu(int gracz, int planszaNR) {
    //Okresla, czy gracz porusza sie w gore czy w dol w zaleznosci od miejsca ustawienia jego pionkow
    if ((gracz == 1 && planszaNR == 0) || (gracz == 2 && planszaNR == 1) || (gracz == 3 && planszaNR == 2)) return -1;
    return 1;
}

int TrzechGraczy::mapujPlansze(int gracz, int wybor) {
    //Zwracanie numeru planszy w zaleznosci od gracza
    if (gracz == 1) return wybor - 1; //Gracz nr 1: plansza nr 1: 0, plansza nr 2: 1
    if (gracz == 2) return (wybor == 1) ? 1 : 2; //Gracz nr 2: plansza nr 1: 1, plansza nr 2: 2
    if (gracz == 3) return (wybor == 1) ? 2 : 0; //Gracz nr 3: plansza nr 1: 2, plansza nr 2: 0
    return -1;
}

void TrzechGraczy::rozmiesc() {
    Dialog::rozmieszczenie();

    //Rozmieszczenie pionkow odbywa sie 27 razy, po 9 pionkow dla kazdego z 3 graczy
    for (int i = 0; i < PNK; ++i) {
        for (int j = 1; j <= 3; ++j) {
            std::cout << std::endl << "Gracz " << j << " ustala pionek: " << rodzajePionkow[i] << " (Plansza 1 lub 2)" << std::endl;

            //Ponizej zostaje okreslony gracz, plansza i rzad startowy, na ktorym beda rozkladane pionki
            //W przypadku podania zajetego pola, gracz musi powtorzyc przypisanie
            while (true) {
                int wybor = Odpowiedz::wyborPlanszy();
                int planszaNR = mapujPlansze(j, wybor);
                int wierszID = (kierunekRuchu(j, planszaNR) == -1) ? 4 : 0;
                char kolumna = Odpowiedz::wyborPola();
                int kolumnaID = toupper(kolumna) - 'A';
                if (Gra::plansza[planszaNR][wierszID][kolumnaID] == 0) {
                    Gra::plansza[planszaNR][wierszID][kolumnaID] = j * 10 + i;
                    break;
                }   
                else
                    std::cout << "To pole jest juz zajete. Wybierz inne miejsce." << std::endl;
            }

            Gra::rysujPlansze(0);
            Gra::rysujPlansze(1);
            Gra::rysujPlansze(2);
        }
    }
}

void TrzechGraczy::ruchGracza() {
    //Kazdy z graczy wykonuje ruch
    for (int tura = 1; tura <= 3; ++tura) {
        
        //Sprawdzanie dostepnosci ruchu
        if (!graczMaPionki3(tura) || !graczMozeWykonacRuch3(tura)) {
            std::cout << std::endl << "Gracz " << tura << " nie ma mozliwych ruchow lub pionkow. Pomijanie tury." << std::endl;
            continue;
        }

        //Wybor pionka
        std::cout << std::endl << "///////// TURA GRACZA " << tura << "/////////" << std::endl;
        std::cout << "Wybierz plansze (1 lub 2)" << std::endl;
        int wybor = Odpowiedz::wyborPlanszy();
        int planszaNR = mapujPlansze(tura, wybor);
        int kierunekPionka = kierunekRuchu(tura, planszaNR);

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
            nowyWiersz += kierunekPionka;
            break;
        case 2:
            nowyWiersz += kierunekPionka;
            nowaKolumna -= 1;
            break;
        case 3:
            nowyWiersz += kierunekPionka;
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
                if ((tura == 1 && nowyWiersz == 0 && planszaNR == 0) || (tura == 2 && nowyWiersz == 0 && planszaNR == 1) || (tura == 3 && nowyWiersz == 0 && planszaNR == 2)) {
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
        Gra::rysujPlansze(2);
    }
}

bool TrzechGraczy::graczMozeWykonacRuch3(int gracz) {
    //Sprawdzanie kazdego z pionkow na kazdej planszy
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX; ++j) {
            for (int k = 0; k < MAX; ++k) {
                int pion = plansza[i][j][k];
                if (pion / 10 != gracz) continue;

                //Ustalanie kierunku ruchu wedlug gracza i planszy
                int kierunek = 0;
                if (gracz == 1) {
                    kierunek = (i == 0) ? -1 : 1;
                }
                else if (gracz == 2) {
                    kierunek = (i == 1) ? -1 : 1;
                }
                else if (gracz == 3) {
                    kierunek = (i == 2) ? -1 : 1;
                }

                int nowyWiersz = j + kierunek;
                if (nowyWiersz < 0 || nowyWiersz >= MAX) continue;
                //Wprost
                if (plansza[i][nowyWiersz][k] == 0) return true;
                //Ukosnie w lewo
                if (k > 0 && plansza[i][nowyWiersz][k - 1] == 0) return true;
                //Ukosnie w prawo
                if (k < MAX - 1 && plansza[i][nowyWiersz][k + 1] == 0) return true;
            }
        }
    }
    return false;
}

bool TrzechGraczy::graczMaPionki3(int gracz) {
    //Przejrzenie wszystkich plansz w celu odnalezienia jakiegokolwiek pionka uzytkownika
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX; ++j) {
            for (int k = 0; k < MAX; ++k) {
                int pion = plansza[i][j][k]; //Pobieranie wartosci z planszy
                if (pion / 10 == gracz) return true;
            }
        }
    }
    return false;
}

void TrzechGraczy::rozgrywka() {
    for (int i = 0; i < 3; ++i) {
        std::cout << "GRACZ NR " << i + 1 << std::endl;
        gracz[i].pytajONazwe();
    }
    rozmiesc(); //Rozstawienie pionkow przez graczy
    Dialog::rozgrywanie();
    //Gra trwa dopoki gracze maja mozliwosci ruchu
    while (true) {
        ruchGracza();

        bool gracz1aktywny = graczMaPionki3(1) && graczMozeWykonacRuch3(1);
        bool gracz2aktywny = graczMaPionki3(2) && graczMozeWykonacRuch3(2);
        bool gracz3aktywny = graczMaPionki3(3) && graczMozeWykonacRuch3(3);

        if (!gracz1aktywny && !gracz2aktywny && !gracz3aktywny) {
            std::cout << std::endl << "Gra zakonczona - zaden gracz nie moze wykonac ruchu lub nie ma pionkow." << std::endl;
            std::cout << std::endl << "Wyniki:" << std::endl;
            for (int i = 0; i < 3; ++i) {
                std::cout << gracz[i].getNazwa() << " - " << gracz[i].getPunkty() << " punktow" << std::endl;
                Ranking::zapiszDoPliku(gracz[i]);
            }
            Ranking::wyswietlRanking();
            break;
        }
    }
}