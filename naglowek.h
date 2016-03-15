//#include <stdio.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include "conio2.h"


#define POLE tab[i][j]
#define HUD_X 25
#define HELP_X 55
#define START_Y 2
#define START_X 2
#define AKTUALNY_SEGMENT tab[y-(START_Y-1)][x-(START_X-1)]
#define AKTUALNY_X x-(START_X-1)
#define AKTUALNY_Y y-(START_Y-1)


using namespace std;


struct pole
{
	int wartosc;
	int kolor;
	int komentarz[9];
};


typedef struct element
{
	int stary_komentarz[9];
	int nowy_komentarz[9];
	int numer_kolumny;
	int numer_wiersza;
	int stara_wartosc;
	int nowa_wartosc;
	element *nastepny;
	element *poprzedni;
}nowy;


void stworz_glowe(element *head);


void usun(element *miejsce_startu);


void dodaj(int stara_wartosc, int nowa_wartosc, int x_punktu, int y_punktu, element *poprzednik, int nowy_komentarz[9], int stary_komentarz[9]);


void zmien_kolor_na_domyslny(pole tab[19][19], int attr);


void przepisz(int komentarz_startu[9], int komentarz_docelowy[9]);


void przepisz(pole tab[19][19], char kopia[81], int numer_wiersza);


void importuj(pole tab[19][19]);


void wypisz_nazwe(char nazwa[100], int i);


void eksportuj(pole tab[19][19]);


void rysuj_tablice(pole tab[19][19]);


void wracaj(pole tab[19][19]);


void podswietl(pole tab[19][19], int attr, int *podswietlona, int x, int y, double czas, int *licznik_ruchow);


void wystartuj_tablice(pole tab[19][19]);


int porownaj_sekcje(pole tab[19][19], int poczatek_x, int poczatek_y, int x, int y, int zn, int stara_wartosc);


int testuj_sekcje(pole tab[19][19], int x, int y, int zn, int stara_wartosc);


void zmien_komentarz(pole tab[19][19], int x, int y, element *identyfikator);


void wypisz_komentarz(pole tab[19][19], int x, int y);


int testuj_wiersz(pole tab[19][19], int x, int y, int zn, int stara_wartosc);


int testuj_kolumne(pole tab[19][19], int x, int y, int zn, int stara_wartosc);


void pomoz(pole tab[19][19], int x, int y, int stara_wartosc);


void daj_interfejs(pole tab[19][19], int licznik_ruchow, int x, int y, double czas_poczatkowy);


int sprawdz_wszystko(pole tab[19][19], int x, int y, int zn, int stara_wartosc);


void zrob_za_mnie(pole tab[19][19], int *licznik_ruchow);