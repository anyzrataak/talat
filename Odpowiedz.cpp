#define _CRT_SECURE_NO_WARNINGS
#include "Odpowiedz.h"
#include "Dialog.h"
#include <iostream>

int Odpowiedz::wyborTrybu() {
    Dialog::trybRozgrywki();
    //Pobieranie od uzytkownika nr trybu rozgrywki i sprawdzanie jego poprawnosci
    int wybor = 0;
    while (true) {
        std::cout << "DECYZJA: ";
        std::cin >> wybor;
        if (wybor == 1 || wybor == 2 || wybor == 3) break;
        std::cerr << std::endl << "Wprowadzone bledne dane, prosze poprawic" << std::endl << std::endl;
    }
    return wybor;
}

int Odpowiedz::wyborPlanszy() {
    //Pobieranie od uzytkownika nr planszy i sprawdzanie jego poprawnosci
    int wybor = 0;
    while (true) {
        std::cout << "DECYZJA: ";
        std::cin >> wybor;
        if (wybor == 1 || wybor == 2) break;
        std::cerr << std::endl << "Wprowadzone bledne dane, prosze poprawic" << std::endl << std::endl;
    }
    return wybor;
}

char Odpowiedz::wyborPola() {
    //Pobieranie od uzytkownika litery reprezentujacej kolumne i sprawdzanie jej poprawnosci
    char wybor;
    while (true) {
        std::cout << "DECYZJA: ";
        std::cin >> wybor;
        if (wybor == 'a' || wybor == 'A' || wybor == 'b' || wybor == 'B' || wybor == 'c' || wybor == 'C' || wybor == 'd' || wybor == 'D' || wybor == 'e' || wybor == 'E') break;
        std::cerr << std::endl << "Wprowadzone bledne dane, prosze poprawic" << std::endl << std::endl;
    }
    return wybor;
}

int Odpowiedz::wyborWiersza() {
    //Pobieranie od uzytkownika nr wiersza i sprawdzanie jego poprawnosci
    int wybor = 0;
    while (true) {
        std::cout << "DECYZJA: ";
        std::cin >> wybor;
        if (wybor >= 1 && wybor <= 5) break;
        std::cerr << std::endl << "Wprowadzone bledne dane, prosze poprawic" << std::endl << std::endl;
    }
    return wybor;
}

char Odpowiedz::wyborNastepnejGry() {
    //Pobieranie od uzytkownika litery determinujacej chec dalszej rozgrywki i sprawdzanie jej poprawnosci
    char wybor;
    while (true) {
        std::cout << "DECYZJA: ";
        std::cin >> wybor;
        if (wybor == 't' || wybor == 'n' || wybor == 'T' || wybor == 'N') break;
        std::cerr << std::endl << "Wprowadzone bledne dane, prosze poprawic" << std::endl << std::endl;
    }
    return wybor;
}

int Odpowiedz::wyborKierunku() {
    //Pobieranie od uzytkownika nr ruchu pionka i sprawdzanie jego poprawnosci
    int wybor;
    while (true) {
        std::cout << "DECYZJA: ";
        std::cin >> wybor;
        if (wybor >= 1 && wybor <= 5) break;
        std::cerr << std::endl << "Wprowadzone bledne dane, prosze poprawic" << std::endl << std::endl;
    }
    return wybor;
}