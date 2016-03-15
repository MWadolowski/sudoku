#include "naglowek.h"



void przepisz(pole tab[19][19], char kopia[81], int numer_wiersza)
{
	for (int i = 1; i < 18; i += 2)
	{

		if (tab[numer_wiersza][i].wartosc != ' ')
			kopia[((i - 1) / 2) + (9 * (numer_wiersza - 1) / 2)] = tab[numer_wiersza][i].wartosc;
		else
			kopia[((i - 1) / 2) + (9 * (numer_wiersza - 1) / 2)] = '-';
	}
}


void importuj(pole tab[19][19])
{
	char wczytana;
	char a;
	int i = 0;
	char nazwa[100];
	int tymczasowa_tablica[81];

	gotoxy(HELP_X, 1);
	cout << "podaj nazwe pliku";
	
	while (a = getchar())
	{ 
		if (a == 13)
		{
			break;
		}
		nazwa[i] = a;
		wypisz_nazwe(nazwa, i);
		i++;
	}
	nazwa[i] = '.';
	nazwa[i + 1] = 't';
	nazwa[i + 2] = 'x';
	nazwa[i + 3] = 't';
	nazwa[i + 4] = '\0';

	ifstream plik(nazwa);



	
	for (int i = 1; i < 18; i += 2)
	{
		for (int j = 1; j < 18; j += 2)
		{
			plik >> wczytana;

			if (wczytana == '-')
			{
				POLE.wartosc = ' ';
			}
			else
			{
				POLE.wartosc = wczytana;
			}
		}
	}
	
	plik.close();
	wracaj(tab);
}


void wypisz_nazwe(char nazwa[100], int i)
{
	for (int j = 0; j <= i; j++)
	{
		gotoxy(HELP_X + j, 6);
		cout << nazwa[j];
	}
}


void eksportuj(pole tab[19][19])
{
	char a;
	char nazwa[100];
	int i = 0;

	gotoxy(HELP_X, 1);
	cout << "podaj nazwe pliku";


	while (a = getchar())
	{
		if (a == 13)
		{
			break;
		}
		nazwa[i] = a;
		wypisz_nazwe(nazwa, i);
		i++;
	}

	nazwa[i] = '.';
	nazwa[i + 1] = 't';
	nazwa[i + 2] = 'x';
	nazwa[i + 3] = 't';
	nazwa[i + 4] = '\0';

	char kopia[81];
	for (int i = 1; i < 18; i+=2)
	{
		przepisz(tab, kopia, i);
	}

	ofstream plik(nazwa, ios::app);

	//plik << "<board nr" << (*licznik_ruchow) + 1 << ">" << endl;

	for (int i = 0; i < 81; i++)
	{
		plik << kopia[i];
		if ((i + 1) % 9 == 0)
		{
			plik << endl;
		}
	}

	//plik << "</board>" << endl;


	plik.close();
}