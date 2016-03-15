#include "naglowek.h"









int main()
{

	element start;
	stworz_glowe(&start);
	element *identyfikator = &start;

	clock_t czas_poczatkowy = clock();
	clock_t czas_teraz;

	int podswietlona_liczba = NULL;
	int zmienna_wyjscia;
	int kopia_x;
	int kopia_y;
	int stara_wartosc;
	textbackground(BLUE);
	int licznik_ruchow = 0;
	pole tab[19][19];
	int zn, x = START_X, y = START_Y, attr = 7;	
	settitle("Michal Wadolowski 155219");

	
	clrscr();
	zmien_kolor_na_domyslny(tab, attr);
	wystartuj_tablice(tab);
	rysuj_tablice(tab);

	do 
	{	
		//wracaj(tab);
		czas_teraz = clock();
		textcolor(7);
		daj_interfejs(tab, licznik_ruchow, x, y, (czas_teraz-czas_poczatkowy)/CLOCKS_PER_SEC);
		gotoxy(x, y);
		textcolor(attr);
		//putch(' ');
		zn = getch();
		stara_wartosc = AKTUALNY_SEGMENT.wartosc;



		if (zn == 'u' && identyfikator->poprzedni != NULL)//undo
		{
			tab[(identyfikator->numer_wiersza)][(identyfikator->numer_kolumny)].wartosc = identyfikator->stara_wartosc;
			przepisz(identyfikator->stary_komentarz, tab[(identyfikator->numer_wiersza)][(identyfikator->numer_kolumny)].komentarz);
			identyfikator = identyfikator->poprzedni;
			licznik_ruchow++;
			wracaj(tab);

		}


		if (zn == 'r' && identyfikator->nastepny != NULL)//redo
		{
			identyfikator = identyfikator->nastepny;
			tab[(identyfikator->numer_wiersza)][(identyfikator->numer_kolumny)].wartosc = identyfikator->nowa_wartosc;
			przepisz(identyfikator->nowy_komentarz, tab[(identyfikator->numer_wiersza)][(identyfikator->numer_kolumny)].komentarz);
			licznik_ruchow++;
			wracaj(tab);
		}


		if(zn >= '1' && zn <= '9' && AKTUALNY_SEGMENT.wartosc != zn && sprawdz_wszystko(tab, x, y, zn, stara_wartosc) == 0)
		{
			if (identyfikator->nastepny != NULL)
			{
				usun(identyfikator->nastepny);
				identyfikator->nastepny = NULL;
			}

			dodaj(AKTUALNY_SEGMENT.wartosc, zn, AKTUALNY_X, AKTUALNY_Y, identyfikator, AKTUALNY_SEGMENT.komentarz, AKTUALNY_SEGMENT.komentarz);
			identyfikator = identyfikator->nastepny;
			AKTUALNY_SEGMENT.wartosc = zn;
			AKTUALNY_SEGMENT.kolor = attr;
			licznik_ruchow++;
			if (zn == podswietlona_liczba)
			{
				AKTUALNY_SEGMENT.kolor = attr + 1;
			}
			textcolor(AKTUALNY_SEGMENT.kolor);
			cout<<(char)zn;//wpisz do tabeli liczbe

			
		}





		else if(zn == 0x08 && AKTUALNY_SEGMENT.wartosc != ' ')//backspace
		{
			if (identyfikator->nastepny != NULL)
			{
				usun(identyfikator->nastepny);
				identyfikator->nastepny = NULL;
			}

			dodaj(AKTUALNY_SEGMENT.wartosc, zn, AKTUALNY_X, AKTUALNY_Y, identyfikator, AKTUALNY_SEGMENT.komentarz, AKTUALNY_SEGMENT.komentarz);
			identyfikator = identyfikator->nastepny;
			licznik_ruchow++;
			AKTUALNY_SEGMENT.wartosc = ' ';
			AKTUALNY_SEGMENT.kolor = attr;
			cout<<' ';
		}


		else if(zn == 'p')
		{
			zrob_za_mnie(tab, &licznik_ruchow);
			wracaj(tab);	
		}


		else if (zn == 'g')
		{

			podswietl(tab, attr, &podswietlona_liczba, x, y, (czas_teraz - czas_poczatkowy) / CLOCKS_PER_SEC, &licznik_ruchow);
		}


		else if (zn == 's')
		{
			eksportuj(tab);
			licznik_ruchow++;
			wracaj(tab);
		}

		else if (zn == 'i')
		{
			importuj(tab);
			wracaj(tab);
		}



		else if (zn == 'k')
		{
			zmien_komentarz(tab, x, y, identyfikator);
		}



		else if(zn == 'l')
		{
			stara_wartosc = AKTUALNY_SEGMENT.wartosc;
			kopia_x = x;
			kopia_y = y;
			gotoxy(55, 1);
			cout<<"mozna wpisac"<<endl;
			gotoxy(55, 2);
			pomoz(tab, kopia_x, kopia_y, stara_wartosc);
			gotoxy(55, 3);
			cout<<"zeby wyjsc wcisnij z";
			while(zmienna_wyjscia = getchar())
			{
				if(zmienna_wyjscia == 'z')
				{
					wracaj(tab);
					break;
				}
			}

		}


		
						
			if(zn == 0x48 && y>START_Y) 
				y-=2;//w gore
			else if(zn == 0x50 && y<START_Y+16) //przeskakuje o 2 zeby nie wymazywac tabeli
				y+=2;//w dol	
			else if(zn == 0x4b && x>START_X) 
				x-=2;//w lewo
			else if(zn == 0x4d && x<START_X+16) 
				x+=2;//w prawo
		

		//else if(zn == ' ') attr = (attr + 1) % 16;
	} 
	while (zn != 'q');
	return 0;
}

