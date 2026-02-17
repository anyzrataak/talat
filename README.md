Projekt stanowi implementacje logicznej gry planszowej Talat, zrealizowana w jezyku C++ jako zadanie semestralne z przedmiotuProgramowanie Obiektowe [2. semestr studiow, dnia 2.06.2025]. Glownym celem aplikacji jest wierne odwzorowanie zasad oryginalu 
przy jednoczesnym wykorzystaniu mechanizmow paradygmatu obiektowego. Architektura systemu opiera sie na hierarchii klas, gdzie klasa bazowa Gra definiuje wspolny interfejs i metody abstrakcyjne dla klas pochodnych: JedenGracz, DwochGraczy oraz TrzechGraczy. 
Takie podejscie pozwolilo na zastosowanie polimorfizmu oraz dziedziczenia w celu obslugi roznych trybow rozgrywki, w tym gry z wirtualnym przeciwnikiem.

Program dziala w trybie konsolowym. Logika obejmuje pelny cykl partii, od fazy rozmieszczania pionkow na planszach po zarzadzanie mechanika bicia i ruchem.
Za warstwe komunikacji i interfejsu odpowiada klasa Dialog, natomiast trwalosc danych zapewnia klasa Ranking, ktora zarzadza zapisem i sortowaniem wynikow w zewnetrznym pliku tekstowym ranking.txt.
