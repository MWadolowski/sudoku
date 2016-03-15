#include "naglowek.h"


void stworz_glowe(element *head)
{
	head->nastepny = NULL;
	head->poprzedni = NULL;
}


void usun(element *miejsce_startu)//nastepca identyfikatora
{
	if (miejsce_startu->nastepny != NULL)
	{
		usun(miejsce_startu->nastepny);
	}

	free(miejsce_startu);
}


void przepisz(int komentarz_startu[9], int komentarz_docelowy[9])
{
	for (int i = 0; i < 9; i++)
	{
		komentarz_docelowy[i] = komentarz_startu[i];
	}
}


void dodaj(int stara_wartosc, int nowa_wartosc, int x_punktu, int y_punktu, element *poprzednik, int nowy_komentarz[9], int stary_komentarz[9])
{
	if (poprzednik->nastepny != NULL)
	{
		usun(poprzednik->nastepny);
	}

	nowy *x = (nowy *)malloc(sizeof(nowy));
	x->nastepny = NULL;
	x->poprzedni = poprzednik;
	x->stara_wartosc = stara_wartosc;
	x->nowa_wartosc = nowa_wartosc;
	x->numer_kolumny = x_punktu;
	x->numer_wiersza = y_punktu;
	przepisz(stary_komentarz, x->stary_komentarz);
	przepisz(nowy_komentarz, x->nowy_komentarz);
	poprzednik->nastepny = x;
}
