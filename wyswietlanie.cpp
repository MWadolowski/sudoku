#include "naglowek.h"


void rysuj_tablice(pole tab[19][19])
{
	for (int i = 0; i <19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					POLE.wartosc = 218;//lewy gorny rog
				}

				else if (j == 18)
				{
					POLE.wartosc = 191;//prawy gorny rog	
				}

				else if (j % 2 == 0 && j != 0 && j != 18)
				{
					if (j % 6 == 0 && j != 0 && j != 18)
					{
						POLE.wartosc = 203;//krawedz gorna podwojna z wypustka
					}

					else
					{
						POLE.wartosc = 194;//krawedz gorna z wypustka	
					}
				}
			}


			if (i == 18)
			{
				if (j == 0)
				{
					POLE.wartosc = 192;//lewy dolny rog
				}

				else if (j == 18)
				{
					POLE.wartosc = 217;	//prawy dolny rog
				}

				else if (j % 2 == 0 && j != 0 && j != 18)
				{
					if (j % 6 == 0)
					{
						POLE.wartosc = 202;//krawedz dolna podwojna z wypustka
					}
					else
					{
						POLE.wartosc = 193;//krawedz dolna z wypustka
					}
				}
			}


			if (j == 0 && i % 2 == 0 && i != 0 && i != 18)
			{
				if (i % 6 == 0)
				{
					POLE.wartosc = 204;//krawedz lewa podwojna z wypustka
				}
				else
				{
					POLE.wartosc = 195;//krawedz lewa z wypustka
				}

			}


			if (j == 18 && i % 2 == 0 && i != 0 && i != 18)
			{
				if (i % 6 == 0)
				{
					POLE.wartosc = 185;//krawedz prawa podwojna z wypustka 
				}

				else
				{
					POLE.wartosc = 180;//krawedz prawa z wypustka
				}
			}


			if (i % 2 == 1 && j % 2 == 0)
			{
				if (j % 6 == 0 && j != 0 && j != 18)
				{
					POLE.wartosc = 186;//krawedz boczna podwojna
				}

				else
				{
					POLE.wartosc = 179;//krawedz boczna
				}
			}


			if (i % 2 == 0 && j % 2 == 1)
			{
				if (i % 6 == 0 && i != 0 && i != 18)
				{
					POLE.wartosc = 205;//krawedz gorna podwojna
				}

				else
				{
					POLE.wartosc = 196;//krawedz gorna
				}
			}


			if (i % 2 == 0 && j % 2 == 0 && i != 0 && i != 18 && j != 0 && j != 18)
			{
				if (j % 6 == 0 && i % 6 == 0)
				{
					POLE.wartosc = 206;//srodek podwojny
				}

				else if ((i % 6 == 0 && j % 6 != 0) || (i % 6 != 0 && j % 6 == 0))
				{
					POLE.wartosc = 206;//srodek podwojny czesciowo//	(216)DO ZMIANY!!
				}

				else
				{
					POLE.wartosc = 197;//srodek
				}
			}
	
			textcolor(POLE.kolor);
			gotoxy(START_X - 1 + j, START_Y - 1 + i);
			cout << (char)(POLE.wartosc);
		}
		cout << endl;
	}
}


void wracaj(pole tab[19][19])
{
	clrscr();
	gotoxy(START_X-1, START_Y-1);
	rysuj_tablice(tab);
}


void zmien_komentarz(pole tab[19][19], int x, int y, element *identyfikator)
{
	int akcja;
	int kopia_komentarza[9];
	przepisz(AKTUALNY_SEGMENT.komentarz, kopia_komentarza);

	gotoxy(HELP_X, 1);
	cout << "skomentuj";
	gotoxy(HELP_X, 2);
	cout << "wcisnij z zeby wrocic";

	while (akcja = getchar())
	{
		if (akcja >= '1' && akcja <= '9')
		{
			if (AKTUALNY_SEGMENT.komentarz[(int)akcja - 48 - 1] != (int)akcja - 48)
			{
				AKTUALNY_SEGMENT.komentarz[(int)akcja - 48 - 1] = (int)akcja - 48;
				dodaj(AKTUALNY_SEGMENT.wartosc, AKTUALNY_SEGMENT.wartosc, AKTUALNY_X, AKTUALNY_Y, identyfikator, AKTUALNY_SEGMENT.komentarz, kopia_komentarza);
			}

			else
			{
				AKTUALNY_SEGMENT.komentarz[(int)akcja - 48 - 1] = 0;
				dodaj(AKTUALNY_SEGMENT.wartosc, AKTUALNY_SEGMENT.wartosc, AKTUALNY_X, AKTUALNY_Y, identyfikator, AKTUALNY_SEGMENT.komentarz, kopia_komentarza);
			}
		}

		if (akcja == 'z')
		{
			wracaj(tab);
			break;
		}

	}
}


void podswietl(pole tab[19][19], int attr, int *podswietlona, int x, int y, double czas, int *licznik_ruchow)
{
	int wybrana_liczba;

	if (*podswietlona != NULL)
	{
		*podswietlona = NULL;
		zmien_kolor_na_domyslny(tab, attr);
		wracaj(tab);
		daj_interfejs(tab, *licznik_ruchow, x, y, czas);
		
	}

	gotoxy(HELP_X, 1);
	cout << "wybierz liczbe do";
	gotoxy(HELP_X, 2);
	cout << "podswietlenia";
	gotoxy(HELP_X, 3);
	cout<< "zeby wrocic i wyzerowac: z";

	while (wybrana_liczba = getchar())
	{
		if (wybrana_liczba == 'z')
			break;

		if (wybrana_liczba >= '1' && wybrana_liczba <= '9')
		{
			*podswietlona = wybrana_liczba;

			for (int i = 1; i < 18; i += 2)
			{
				for (int j = 1; j < 18; j += 2)
				{
					if (POLE.wartosc == wybrana_liczba)
					{
						POLE.kolor = attr + 1;
						gotoxy(START_X - 1 + j, START_Y - 1 + i);
						cout << (char)(POLE.wartosc);
						textcolor(attr);
					}
				}
			}
			break;
		}
	}

	wracaj(tab);
}


void zmien_kolor_na_domyslny(pole tab[19][19], int attr)
{
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<19; j++)
		{
			POLE.kolor = attr;
		}
	}
}


void wystartuj_tablice(pole tab[19][19])//nadaje startowe wartosci dla pol modyfikowalnych
{
	for (int i = 1; i<18; i += 2)
	{
		for (int j = 1; j<18; j += 2)
		{
			POLE.wartosc = ' ';
		}
	}
}


void pomoz(pole tab[19][19], int x, int y, int stara_wartosc)
{
	for (int i = '1'; i <= '9'; i++)
	{
		if (testuj_wiersz(tab, x, y, i, stara_wartosc) + testuj_kolumne(tab, x, y, i, stara_wartosc) + testuj_sekcje(tab, x, y, i, stara_wartosc) == 0)
		{
			cout << (char)i << " ";
		}
	}
}


void wypisz_komentarz(pole tab[19][19], int x, int y)
{
	int licznik_komentarzy = 0;

	for (int i = 0; i < 9; i++)
	{
		if (AKTUALNY_SEGMENT.komentarz[i] == i + 1)//przypisuje indeksowi 0-1, 1-2 itd
		{
			licznik_komentarzy++;
			cout << i+1 << " ";
		}
	}
	if (licznik_komentarzy == 0)
		cout << "-            ";
}


void daj_interfejs(pole tab[19][19], int licznik_ruchow, int x, int y, double czas_poczatkowy)
{
	gotoxy(HUD_X, 1);
	cout << ("q = wyjscie");
	gotoxy(HUD_X, 2);
	cout << "l = pomoc";
	gotoxy(HUD_X, 3);
	cout << "p = autouzupelnianie";
	gotoxy(HUD_X, 4);
	cout << "g = zaznaczenie";
	gotoxy(HUD_X, 5);
	cputs("u = undo");
	gotoxy(HUD_X, 6);
	cout << "r = redo";
	gotoxy(HUD_X, 7);
	cout << "s = save";
	gotoxy(HUD_X, 8);
	cout << "i = load";
	gotoxy(HUD_X, 9);
	cout << ("strzalki = poruszanie");
	gotoxy(HUD_X, 10);
	cout << "aktualna pozycja: " << ((y - START_Y) / 2) + 1 << " " << ((x - START_X) / 2) + 1;//podzielona na 2 ze wzgledu na to ze elementy tabeli tez zajmuja czesc tablicy...
	gotoxy(HUD_X, 11);								//...dzieki temu nie wybierze pozycji na ktorej znajduje sie czesc "graficzna"
	cout << "aktualna ilosc ruchow: " << licznik_ruchow;
	gotoxy(HUD_X, 12);
	cout << "minelo: " << czas_poczatkowy << " sekund";
	gotoxy(HUD_X, 13);
	cout << "komentarz:";
	gotoxy(HUD_X, 14);
	wypisz_komentarz(tab, x, y);
	//gotoxy(HUD_X, 15);
	//cout << AKTUALNY_SEGMENT.wartosc;
}


void zrob_za_mnie(pole tab[19][19], int *licznik_ruchow)
{
	int reakcja;
	int zapamietany_x;
	int zapamietany_y;
	int zapamietane_rozwiazanie;
	int ilosc_rozwiazan = 0;

	for (int wiersz = 1; wiersz<19; wiersz += 2)
	{
		for (int kolumna = 1; kolumna<19; kolumna += 2)
		{
			if (tab[wiersz][kolumna].wartosc == ' ')
			{
				for (int z = '1'; z <= '9'; z++)
				{
					if (sprawdz_wszystko(tab, kolumna + 1, wiersz + 1, z, ' ') == 0)
					{
						ilosc_rozwiazan++;
						zapamietany_x = kolumna;
						zapamietany_y = wiersz;
						zapamietane_rozwiazanie = z;
					}

					if (ilosc_rozwiazan > 1)
						break;
				}
			}
			if (ilosc_rozwiazan == 1)
				break;
			ilosc_rozwiazan = 0;
		}
		if (ilosc_rozwiazan == 1)
			break;
		ilosc_rozwiazan = 0;
	}

	if (ilosc_rozwiazan == 1)
	{
		gotoxy(50, 1);
		cout << "w polu " << (zapamietany_y + 1) / 2 << " " << (zapamietany_x + 1) / 2 << " mozna wpisac " << (char)zapamietane_rozwiazanie;
		gotoxy(50, 2);
		cout << "wcisnij p zeby je wstawic";
		gotoxy(50, 3);
		cout << "wcisnij z zeby powrocic";
		while (reakcja = getchar())
		{
			if (reakcja == 'p')
			{
				(*licznik_ruchow)++;
				tab[zapamietany_y][zapamietany_x].wartosc = zapamietane_rozwiazanie;
				wracaj(tab);
				break;
			}

			else if (reakcja == 'z')
			{
				wracaj(tab);
				break;

			}
		}
	}
	else
	{
		gotoxy(50, 1);
		cout << "brak jednoznacznych rozwiazan";
		gotoxy(50, 2);
		cout << "wcisnij z zeby powrocic";

		while (reakcja = getchar())
		{
			if (reakcja == 'z')
			{
				wracaj(tab);
				break;
			}
		}
	}
}