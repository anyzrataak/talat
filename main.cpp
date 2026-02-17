#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include "Gra.h"
#include "Dialog.h"
#include "Odpowiedz.h"
#include "JedenGracz.h"
#include "DwochGraczy.h"
#include "TrzechGraczy.h"
#include "Gracz.h"
#include "Ranking.h"

int main(void) {
    Dialog::powitanie();
    Dialog::zasady();

    char decyzja = 't'; //Determinuje ilosc rozegranych gier w ciagu jednego uruchomienia programu
    while (decyzja == 't' || decyzja == 'T') {
        int ilosc = Odpowiedz::wyborTrybu(); //Wybranie trybu gry dla jednego, dwoch lub trzech graczy

        //Dynamiczne tworzenie odpowiedniego obiektu gry w zaleznoœci od liczby graczy
        Gra* gra = nullptr;
        if (ilosc == 3)
            gra = new TrzechGraczy();
        else if (ilosc == 2)
            gra = new DwochGraczy();
        else if (ilosc == 1)
            gra = new JedenGracz();

        //Uruchomienie gry zgodnie z dokonanym przez uzytkownika wyborem
        gra->rozgrywka();

        delete gra;

        std::cout << "Czy chcesz zagrac ponownie? (t/n): ";
        decyzja = Odpowiedz::wyborNastepnejGry();
    }

	system("pause");
    return 0;
}