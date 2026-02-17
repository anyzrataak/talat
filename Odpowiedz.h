#pragma once

class Odpowiedz {
public:
    //Pobiera od uzytkownika nr trybu rozgrywki i sprawdza jego poprawnosc [1, 3]
    //return: wybor - poprawny skladniowo wybor gracza
    static int wyborTrybu();
    //Pobiera od uzytkownika nr planszy i sprawdza jego poprawnosc [1, 2]
    //return: wybor - poprawny skladniowo wybor gracza
    static int wyborPlanszy();
    //Pobiera od uzytkownika litere reprezentujaca kolumne i sprawdza jej poprawnosc [A-E]
    //return: wybor - poprawny skladniowo wybor gracza
    static char wyborPola();
    //Pobiera od uzytkownika nr wiersza i sprawdza jego poprawnosc [1, 5]
    //return: wybor - poprawny skladniowo wybor gracza
    static int wyborWiersza();
    //Pobiera od uzytkownika litere determinujaca chec dalszej rozgrywki i sprawdza jej poprawnosc [t/T, n/N]
    //return: wybor - poprawny skladniowo wybor gracza
    static char wyborNastepnejGry();
    //Pobiera od uzytkownika nr kierunku pionka i sprawdza jego poprawnosc [1, 5]
    //return: wybor - poprawny skladniowo wybor gracza
    static int wyborKierunku();
};