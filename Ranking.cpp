#define _CRT_SECURE_NO_WARNINGS
#include "Ranking.h"
#include "Gracz.h"
#include "Dialog.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

#define MAX_NAZWA 30
#define MAX 100

//Zawiera dane wpisow potrzebnych do wyswietlenia rankingu z pliku
struct Wpis {
    //Nazwa gracza
    //Format: [MAX_NAZWA], gdzie:
    //MAX_NAZWA to maksymalna dlugosc nazwy gracza - 30
    char nazwa[MAX_NAZWA];
    int punkty; //Punkty danego gracza
};

void Ranking::zapiszDoPliku(const Gracz& gracz) {
    Wpis wpisy[MAX];
    int ilosc = 0;

    std::ifstream plikIn("ranking.txt");
    while (ilosc < MAX && plikIn >> wpisy[ilosc].nazwa >> wpisy[ilosc].punkty) {
        ilosc++;
    }
    plikIn.close();

    //Sprawdzanie istniejacych graczy
    bool znaleziono = false;
    for (int i = 0; i < ilosc; i++) {
        if (strcmp(wpisy[i].nazwa, gracz.getNazwa()) == 0) {
            znaleziono = true;
            if (gracz.getPunkty() > wpisy[i].punkty) {
                wpisy[i].punkty = gracz.getPunkty(); //Aktualizacja wyniku gracza, jezeli obecny jest lepszy niz wpisany
            }
            break;
        }
    }

    //Umieszczanie nowego gracza w rankingu
    if (!znaleziono && ilosc < 100) {
        strncpy(wpisy[ilosc].nazwa, gracz.getNazwa(), MAX_NAZWA);
        wpisy[ilosc].nazwa[MAX_NAZWA - 1] = '\0';
        wpisy[ilosc].punkty = gracz.getPunkty();
        ilosc++;
    }

    //Sortowanie malejaco
    for (int i = 0; i < ilosc - 1; i++) {
        for (int j = i + 1; j < ilosc; j++) {
            if (wpisy[i].punkty < wpisy[j].punkty) {
                Wpis tymcz = wpisy[i];
                wpisy[i] = wpisy[j];
                wpisy[j] = tymcz;
            }
        }
    }

    //Zapisanie rankingu na nowo
    std::ofstream plikOut("ranking.txt");
    if (plikOut) {
        for (int i = 0; i < ilosc; i++) {
            plikOut << wpisy[i].nazwa << " " << wpisy[i].punkty << "\n";
        }
    }
    plikOut.close();
}

void Ranking::wyswietlRanking() {
    //Otwieranie pliku do wyswietlenia rankingu
    std::ifstream plik("ranking.txt");
    if (!plik) {
        std::cout << "Brak pliku ranking.txt" << std::endl;
        return;
    }

    Dialog::wyswietlanieRankingu();
    std::string nazwa;
    int punkty, i = 1;

    while (plik >> nazwa >> punkty) {
        std::cout << i++ << ". " << nazwa << " - " << punkty << " pkt" << std::endl;
    }
    std::cout << std::endl << std::endl << std::endl;
}