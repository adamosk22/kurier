#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
#ifndef GRAF_H
#define GRAF_H

struct miastoDocelowe
{
	int nazwa;///<numer miasta docelowego
	double odleglosc;///<odleglosc z miasta poczatkowego do miasta docelowego
	miastoDocelowe* pNext;///<wskaznik na nastêpny element
};

struct miastoPoczatkowe
{
	int nazwa;///numer miasta poczatkowego
	miastoDocelowe* pHeadDocelowe;///<wskaznik na pierwsze miasto docelowe
	miastoDocelowe* pTailDocelowe;///<wskaznik na ostatnie miasto docelowe
	miastoPoczatkowe * pNextPoczatkowe;///<wskaznik na kolejny element listy
};

struct listaMiast {
	miastoPoczatkowe* pHead;///<wskaznik na pierwszy element listy miast poczatkowych
	miastoPoczatkowe* pTail;///<wskaznik na ostatni elemt listy miast poczatkowych
	int rozmiar;///<liczba miast poczatkowych
};

struct odwiedzoneMiasto
{
	int nazwa;///< nazwa odwiedzonego miasta
	odwiedzoneMiasto* pNext;///<wskaznik na kolejny element listy
};

struct listaOdwiedzonychMiast
{
	int dluglosc;///<dluglosc wyznaczonej dotychczas trasy
    odwiedzoneMiasto* pHead;///<wskaznik na pierwszy element listy miast odwiedzonych
	odwiedzoneMiasto* pTail;///<wskaznik na ostatni elemt listy miast odwiedzonych
};
/** Funkcja usuwa ostatnio odwiedzone miasto
@param odwiedzone wskaznik na element listy odwiedzonych miast
*/
void usunOstatnieOdwiedzoneMiasto(listaOdwiedzonychMiast** odwiedzone);
/** Funkcja zapisuje wynik do pliku
@param nazwaPliku nazwa pliku wyjsciowego
@param odwiedzoneMiasta lista odwiedzonych miast
@param dlugosc dlugosc trasy minimalnej
*/
void zapiszDoPliku(char* nazwaPliku, listaOdwiedzonychMiast* minOdwiedzoneMiasta, double dlugosc);
/** Funkcja usuwa liste miast docelowych
@param pHead wskaznik na poczatek listy miast docelowych
*/
void usunMiastaDocelowe(miastoDocelowe** pHead);
/** Funkcja dodaje odwiedzone miasto do listy miast odwiedzonych
@param odwiedzoneMiasta wskaznik na liste odwiedzonych miast
@param miasto wskaznik na miasto, ktore ma byc dodane do listy
*/
void dodajOdwiedzoneMiastoDoListy(listaOdwiedzonychMiast** odwiedzoneMiasta, odwiedzoneMiasto* miasto);
/** Funkcja szuka kolejnego miasta
@param odwiedzone odwiedzone wkaznik na liste odwiedzonych miast
*/
void szukajNastepnegoMiasta(listaMiast* pHead, int nazwaKolejnegoMiasta, miastoPoczatkowe** miastoNastepne);
/** Funkcja sprawdza czy wszystkie miasta sa odwiedzone i czy wrocic do pierwszego miasta
@param odwiedzoneMiasta wkaznik na liste odwiedzonych miast
@param liczbaMiastDoOdwiedzenia liczba miast
@param miastoPocz wkaznik na pierwsze miasto poczatkowe
@param miastoNast wskaznik na kolejne miasto poczatkowe
*/
bool sprawdzCzyPowrot(listaOdwiedzonychMiast* odwiedzoneMiasta, int liczbaMiastDoOdwiedzenia, miastoPoczatkowe* miastoPocz, miastoPoczatkowe* miastoNast);
/** Funkcja wyznacza najlepsza trase z danego miasta poczatkowego i wywoluje sie rekurencyjnie
@param pHead wskaznik na liste miast
@param miastoPocz wskaznik na miasto poczatkowe, z ktorego wyznaczana jest sciezka do nastepnego miasta
@param miastoKolejne wkaznik na kolejne miasto do odwiedzenia
@param odwiedzoneMiasta wskaznik na liste odwiedzonych miast
@param minOdwiedzoneMiasta wskaznik na liste odwiedzonych miast, w ktorej trasa jest najkrotsza
@param *dlugoscTrasy wkaznik na dlugosc danej trasy
@param liczbaMiastDoOdwiedzenia liczba miast poczatkowych plus miasto, do ktorego kurier wraca na koncu
@param *minDlugoscTrasy wskaznik na minimalna dlugosc trasy
*/
void wyznaczNajlepszaTrase(listaMiast* pHead, miastoPoczatkowe* miastoPocz, miastoPoczatkowe* miastoKolejne,listaOdwiedzonychMiast** odwiedzoneMiasta, listaOdwiedzonychMiast** minOdwiedzoneMiasta, double *dlugoscTrasy, int liczbaMiastDoOdwiedzenia, double* minDlugoscTrasy, double odleglosc);
/**Funkcja sprawdza czy miasto bylo juz odwiedzone
@param miastoPocz miasto, ktorego szukamy na liscie miast odwiedzonych
@param odwiedzoneMiasta wskaznik na liste miast odwiedzonych
@return 1 jezeli miasto bylo odwiedzone, 0 jezeli miasto nie bylo odwiedzone
*/
bool sprawdzCzyOdwiedzone(miastoPoczatkowe* miastoPocz, listaOdwiedzonychMiast* odwiedzoneMiasta);
/**Funkcja szuka miasta poczatkowego o danej nazwie
@param pHead wskaznik na pierwszy element listu miast poczatkowych
@param znalezioneMiasto wskaznik na znaleziony element listy
@param a nazwa szukanego miasta
*/
void znajdzMiastoPoczatkowe(miastoPoczatkowe* pHead, miastoPoczatkowe** znalezioneMiasto, int a);
/**Funkcja zapisuje miasto do listy miast, do ktorych mozna sie dostac z danego miasta poczatkowego
@param miastoP miasto, z ktorego prowadzi sciezka do miasta docelowego
@param b nazwa miasta docelowego
@param odleglosc odleglosc z miasta poczatkowego do docelowego
*/
void zapiszDoMiastDocelowych(miastoPoczatkowe** miastoP, int b, double odleglosc);
/** Funkcja zapisuje miasto, ktorego nie ma na liscie miast poczatkowych do tej listy i wywoluje funkcje zapiszDoMiastDocelowych
@param a nazwa pierwszego miasta
@param b nazwa drugiego miasta
@param znak symbol, ktory wskazuje na rodzaj sciezki miedzy a i b
@odl odleglosc miedzy miastami a i b
@pHead wkaznik na liste miast
*/
void zapiszDoMiastPoczatkowych(int a, int b, std::string znak, double odl, listaMiast** pHead);
/** Funkcja sprawdza czy sciezka jest jednokierunkowa czy dwukierunkowa i odpowiednio wywoluje funkcje zapiszDoMiastPoczatkowych
@param a pierwsze miasto
@param b drugie miasto
@param znak symbol, ktory wskazuje na rodzaj sciezki miedzy a i b
@odl odleglosc miedzy miastami a i b
@pHead wkaznik na liste miast
*/
void zapiszDoGrafu(int a, int b, std::string znak, double odl, listaMiast** pHead);
/** Funkcja wczytuje uk³ad sciezek z pliku i wywo³uje funkcje zapiszDoGrafu
@param nazwaPliku nazwa pliku wejsciowego
@param pHead wskaznik na liste miast
*/
void wczytajGraf(char* nazwaPliku, listaMiast** pHead);
/**Funkcja kopiuje listê, aby zosta³a zapisana
@param target lista odwiedzonych miast, do której zapisujemy
@param source lista odwiedzonych miast, któr¹ zapisujemy
*/
void kopiujOdwiedzoneMiasta(listaOdwiedzonychMiast** target, listaOdwiedzonychMiast** source);
/** Funkcja usuwa listê odwiedzonych miast
@param pHead wskaznik na liste
*/
void usunOdwiedzoneMiasta(listaOdwiedzonychMiast** pHead);
/** Funkcja usuwa liste miast poczatkowych ³¹cznie z miastami docelowymi
@param pHead wskaznik na liste
*/
void usunListeMiast(listaMiast** pHead);
#endif





