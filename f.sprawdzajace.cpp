#include "naglowek.h"


int porownaj_sekcje(pole tab[19][19], int poczatek_x, int poczatek_y, int x, int y, int zn, int stara_wartosc)
{
	AKTUALNY_SEGMENT.wartosc = zn;
	int blad = 0;
	int porownywarka[9];

	porownywarka[0] = tab[poczatek_y - 1][poczatek_x - 1].wartosc;
	porownywarka[1] = tab[poczatek_y - 1][poczatek_x + 1].wartosc;
	porownywarka[2] = tab[poczatek_y - 1][poczatek_x + 3].wartosc;
	porownywarka[3] = tab[poczatek_y + 1][poczatek_x - 1].wartosc;
	porownywarka[4] = tab[poczatek_y + 1][poczatek_x + 1].wartosc;
	porownywarka[5] = tab[poczatek_y + 1][poczatek_x + 3].wartosc;
	porownywarka[6] = tab[poczatek_y + 3][poczatek_x - 1].wartosc;
	porownywarka[7] = tab[poczatek_y + 3][poczatek_x + 1].wartosc;
	porownywarka[8] = tab[poczatek_y + 3][poczatek_x + 3].wartosc;

	for (int m = 0; m<9; m++)//porownaj wartosci z tej tablicy
	{
		for (int n = 0; n<9; n++)
		{
			if (porownywarka[m] == porownywarka[n] && m != n && porownywarka[m] != ' ' && porownywarka[n] != ' ')
			{
				blad++;
				break;
			}
		}
		if (blad != 0)
			break;
	}
	AKTUALNY_SEGMENT.wartosc = stara_wartosc;
	return blad;
}


int testuj_sekcje(pole tab[19][19], int x, int y, int zn, int stara_wartosc)//testuje segment 3x3
{//licze czesci tablicy od lewej do prawej, zaczynajac od gory
	int blad = 0;//w zaleznosci od tego w ktorej jestesmy cwiartce wywola funkcje porownujaca dla odpowiedniego przedzialu
	if (y<START_Y+5 && x<START_X+5)//I czesc
		blad = porownaj_sekcje(tab, 2, 2, x, y, zn, stara_wartosc);//tab-tablica sudoku, 2,2-wspolrzedne od ktorych funkcja zaczyna porownywanie
	else if (y<START_Y+5 && x>START_X+5 && x<START_X+11)//II czesc			//x,y-wspolrzedne aktualnie modyfikowanego punktu, zn-wpisana przez uzytkownika wartosc
		blad = porownaj_sekcje(tab, 8, 2, x, y, zn, stara_wartosc);
	else if (y<START_Y+5 && x>START_X+11)//III czesc
		blad = porownaj_sekcje(tab, 14, 2, x, y, zn, stara_wartosc);
	else if (y>START_Y+5 && y<START_Y+11 && x<START_X+5)//IV czesc
		blad = porownaj_sekcje(tab, 2, 8, x, y, zn, stara_wartosc);
	else if (y>START_Y+5 && y<START_Y+11 && x>START_X+5 && x<START_Y+11)//V czesc
		blad = porownaj_sekcje(tab, 8, 8, x, y, zn, stara_wartosc);
	else if (y>START_Y+5 && y<START_Y+11 && x>START_X+11)//VI czesc
		blad = porownaj_sekcje(tab, 14, 8, x, y, zn, stara_wartosc);
	else if (y>START_Y+11 && x<START_X+2)//VII czesc
		blad = porownaj_sekcje(tab, 2, 14, x, y, zn, stara_wartosc);
	else if (y>START_Y+11 && x>START_X+5 && x<START_X+11)//VIII czesc
		blad = porownaj_sekcje(tab, 8, 14, x, y, zn, stara_wartosc);
	else if (y>START_Y+11 && x>START_X+11)//IX czesc
		blad = porownaj_sekcje(tab, 14, 14, x, y, zn, stara_wartosc);

	return blad;
}


int testuj_wiersz(pole tab[19][19], int x, int y, int zn, int stara_wartosc)
{
	int blad = 0;
	int s;
	int porownywarka[9];
	AKTUALNY_SEGMENT.wartosc = zn;
	s = -1;


	for (int i = 1; i<19; i += 2)//spisuje do tablicy z wiersza
	{
		if (tab[AKTUALNY_Y][i].wartosc != ' ')
		{
			s++;
			porownywarka[s] = tab[AKTUALNY_Y][i].wartosc;
		}
	}

	for (int i = 0; i <= s; i++)//porownuje
	{
		for (int j = 0; j <= s; j++)
		{
			if (porownywarka[i] == porownywarka[j] && i != j)
			{
				blad++;
				break;
			}
		}
		if (blad != 0)
			break;
	}
	AKTUALNY_SEGMENT.wartosc = stara_wartosc;
	return blad;
}


int testuj_kolumne(pole tab[19][19], int x, int y, int zn, int stara_wartosc)
{	//wartosc podana przez uzytkownika wpisuje do tabeli po czym porownuje wszystkie liczby ktore nie sa bialymi znakami...
	AKTUALNY_SEGMENT.wartosc = zn;						//...jesli cos sie nie zgadza wraca do stanu wyjsciowego, nie nalicza ruchu etc.
	int blad = 0;

	int s = -1;
	int porownywarka[9];

	for (int i = 1; i<19; i += 2)//przepisuje liczby z kolumny (biale znaki pomija) do tablicy
	{
		if (tab[i][AKTUALNY_X].wartosc != ' ')
		{
			s++;
			porownywarka[s] = tab[i][AKTUALNY_X].wartosc;
		}
	}


	for (int i = 0; i <= s; i++)//porownuje wartosci z nowej tablicy
	{
		for (int j = 0; j <= s; j++)
		{
			if (porownywarka[i] == porownywarka[j] && i != j)
			{
				blad++;
				break;
			}
		}
		if (blad != 0)
			break;
	}
	AKTUALNY_SEGMENT.wartosc = stara_wartosc;
	return blad;
}


int sprawdz_wszystko(pole tab[19][19], int x, int y, int zn, int stara_wartosc)
{
	int a = testuj_kolumne(tab, x, y, zn, stara_wartosc);
	int b = testuj_sekcje(tab, x, y, zn, stara_wartosc);
	int c = testuj_wiersz(tab, x, y, zn, stara_wartosc);

	return a + b + c;
}



