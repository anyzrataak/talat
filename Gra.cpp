#define _CRT_SECURE_NO_WARNINGS
#include "Gra.h"
#include <iostream>

const char rodzajePionkow[PNK][NZW] = { "Maly trojkat", "Maly kwadrat", "Maly szesciokat", "Sredni trojkat", "Sredni kwadrat", "Sredni szesciokat", "Duzy trojkat", "Duzy kwadrat", "Duzy szesciokat" };

int Gra::plansza[PLNSZ][MAX][MAX] = {};

Gra::Gra() {
    //Zerowanie planszy
    for (int i = 0; i < PLNSZ; ++i)
        for (int j = 0; j < MAX; ++j)
            for (int k = 0; k < MAX; ++k)
                plansza[i][j][k] = 0;
}

void Gra::rysujPlansze(int n) {
    //Rysowanie planszy dostosowanej do oznaczen wywolywanych w metodach realizujacych rozgrywke
    std::cout << std::endl << "PLANSZA " << n + 1 << std::endl;
    std::cout << "   A  B  C  D  E" << std::endl;
    for (int i = 0; i < MAX; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < MAX; j++) {
            int oznaczenie = plansza[n][i][j];
            //Jezeli pole jest wyzerowane, oznacza to ze nie znajduje sie na nim zaden pionek
            //W przeciwnym wypadku wypisywane zostaje oznaczenie gracza wraz z nr pionka
            if (oznaczenie == 0) {
                std::cout << " . ";
            }
            else {
                int gracz = oznaczenie / 10;
                int pionekNR = oznaczenie % 10;
                switch (gracz) {
                case 1: std::cout << "J" << pionekNR << " "; break;
                case 2: std::cout << "D" << pionekNR << " "; break;
                case 3: std::cout << "T" << pionekNR << " "; break;
                default: std::cout << "?" << pionekNR << " "; break;
                }
            }
        }
        std::cout << std::endl;
    }
}

bool Gra::moznaZbic(int bijacy, int bity) {
    //Sprawdzanie mozliwosci bicia na podstawie nizej przyjetej hierarchii
    if (bijacy == 0 && bity == 8) return true;
    switch (bijacy) {
    case 1: return bity == 0;
    case 2: return bity == 1;
    case 3: return bity <= 2;
    case 4: return bity <= 3;
    case 5: return bity == 0 || bity == 1 || bity == 2 || bity == 4;
    case 6: return bity >= 3 && bity <= 5;
    case 7: return bity >= 3 && bity <= 6;
    case 8: return bity == 3 || bity == 4 || bity == 5 || bity == 7;
    default: return false;
    }
}

bool Gra::graczMaPionki(int gracz) {
    //Przejrzenie wszystkich plansz w celu odnalezienia jakiegokolwiek pionka uzytkownika
    //Metoda zgodna dla rozgrywek dla dwoch graczy
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < MAX; ++j)
            for (int k = 0; k < MAX; ++k)
                if (plansza[i][j][k] / 10 == gracz)
                    return true;
    return false;
}

bool Gra::graczMozeWykonacRuch(int gracz) {
    //Sprawdzanie kazdego z pionkow na kazdej planszy
    //Metoda zgodna dla rozgrywek dla dwoch graczy
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < MAX; ++j)
            for (int k = 0; k < MAX; ++k) {
                int pionekNR = plansza[i][j][k]; //Pobieranie wartosci z planszy
                if (pionekNR / 10 == gracz) {
                    int kierunek = (gracz == 1) ? -1 : 1; //Sprawdzanie kierunku ruchu wzgledem sprawdzanego gracza
                    int nowyWiersz = j + kierunek;
                    if (nowyWiersz < 0 || nowyWiersz >= MAX) continue; //Wyjscie poza plansze
                    //Ruchy zgodne z zasadami
                    if (plansza[i][nowyWiersz][k] == 0) return true;
                    if (k > 0 && plansza[i][nowyWiersz][k - 1] == 0) return true;
                    if (k < MAX - 1 && plansza[i][nowyWiersz][k + 1] == 0) return true;
                }
            }
    return false; //Zaden ruch nie byl mozliwy
}