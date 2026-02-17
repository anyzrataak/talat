#pragma once

#define MAX 5
#define PLNSZ 3
#define PNK 9
#define NZW 20

//Tablica zawierajaca nazwy wszystkich rodzajow pionkow dostepnych w grze
//Format: [PNK][NZW], gdzie:
//PNK to liczba roznych pionkow - 9
//NZW to maksymalna dlugosc nazwy pionka - 20
extern const char rodzajePionkow[PNK][NZW];

class Gra {
protected:
    //Reprezentacja trojwymiarowej planszy gry
    //Format: [PLNSZ][MAX][MAX], gdzie:
    //PLNSZ to liczba plansz - 3
    //MAX to rozmiar jednej planszy w pionie i poziomie - 5x5
    //Kazda komorka zawiera:
    //0: pole puste
    //liczba > 0: zakodowany pionek
    static int plansza[PLNSZ][MAX][MAX];
public:
    //Konstruktor domyslny, zerowanie pol planszy przed nowa gra
    Gra();
    //Zapewnia przebieg rozgrywki, kazda klasa pochodna wykonuje to na swoj sposob
    virtual void rozgrywka() = 0;
    //Zapewnia rozmieszczenie pionkow wedlug regul kazdej z klas pochodnych
    virtual void rozmiesc() = 0;
    //Zapewnia wykonanie ruchu gracza zgodnie z zasadami gry, kazda klasa pochodna sprawdza poprawnosc ruchu wedlug wlasnych regul
    virtual void ruchGracza() = 0;
    //Wizualizacja planszy w konsoli
    //param: n - nr planszy
    static void rysujPlansze(int n);
    //Sprawdza mozliwosc bicia pionkow wedlug ustalonej z gory hierarchii
    //param: bijacy - nr pionka bijacego
    //param: bity - nr pionka bitego
    //return: true - mozliwe bicie
    //return: false - bicie niedostepne
    bool moznaZbic(int bijacy, int bity);
    //Sprawdzanie, czy gracz posiada jakiekolwiek pionki
    //param: gracz - nr sprawdzanego gracza
    //return: true - posiada
    //return: false - nie posiada
    bool graczMaPionki(int gracz);
    //Sprawdzenie, czy gracz moze wykonac jakikolwiek ruch ktorymkolwiek ze swoich pionkow
    //param: gracz - nr sprawdzanego gracza
    //return: true - moze
    //return: false - nie moze
    bool graczMozeWykonacRuch(int gracz);
};