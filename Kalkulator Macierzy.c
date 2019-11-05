#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

#define S_MAX 20
#define MAX_FILENAME 61
#define MAX_FILELIST 30
#define X_LEAVE -3
#define DET_ZERO -4
#define NO_FILE -5
#define NO_MEMORY -6
#define WRONG_SIZE -7
#define CATALOG_ERR -8
#define EMPTY_CATALOG -9
#define _CLEAR_BUFFER while(getchar()!='\n')

void menu (void);
void err (int);
int value_in (short int*, short int);
int matrix_in (short int, short int, double*);
void file_list (short int*, int, char [][MAX_FILENAME]);
int file_matrix_in (short int*, short int*, double**);
int matrix_in_size_unknown (short int*, short int*, double**);
int matrix_in_size_known (short int, short int, double**);
int matrix_in_multip (short int, short int*, double**);
int matrix_in_sqr (short int*, double**);
void matrix_out (short int, short int, const double*);
int file_matrix_out (short int, short int, const double*, const char*);

void addition (short int, short int, const double*, const double*, double*);
void subtraction (short int, short int, const double*, const double*, double*);
void multiplication_number (short int, short int, double, const double*, double*);
void multiplication_matrix (short int, short int, short int, const double*, const double*, double*);
short int sign (short int, short int);
void minor (short int, short int, short int, const double*, double*);
double determinant (short int, const double*);
void cofactor_matrix (short int , const double*, double*);
void transpose (short int, short int, const double*, double*);
int inverse_matrix (short int, const double*, double*);
double inverse_time (short int);
double mean (short int, const double*);
void quicksort (double*, short int, short int);
double median (short int, const double*);

int main (void)
{
	char ch;
	short int a=-1, b=-1, c=-1;
	int y;
	double v=1, *m1=NULL, *m2=NULL, *m3=NULL;
	
	menu();
	while ((ch = getchar()) != 'q')
	{
		if (ch == '\n') continue; //jezeli uzytkownik wcisnal enter nie wprowadzajac zadnego znaku wczytaj raz jeszcze
		_CLEAR_BUFFER; //wyczysc bufor
		putchar('\n');
		switch (ch)
		{
			case 'a':
				puts ("-----DODAWANIE MACIERZY-----");
				puts ("Wprowadzanie pierwszej macierzy");
				if ((y = matrix_in_size_unknown (&a, &b, &m1)) != 0)
				{
					err(y);
					break;
				}
				puts ("\nWprowadzanie drugiej macierzy");
				if ((y = matrix_in_size_known (a, b, &m2)) != 0)
				{
					err(y);
					break;
				}
				m3 = (double*) calloc(a*b, sizeof (*m3));
				if (m3 == NULL)
				{
					err(NO_MEMORY);
					break;
				}
				addition (a, b, m1, m2, m3);
				file_matrix_out (a, b, m3, "Dodawanie");
				puts ("\nMacierz wynikowa:\n");
				matrix_out (a, b, m3);
				break;

			case 'b':
				puts ("-----ODEJMOWANIE MACIERZY-----");
				puts ("Wprowadzanie pierwszej macierzy");
				if ((y = matrix_in_size_unknown (&a, &b, &m1)) != 0)
				{
					err(y);
					break;
				}
				puts ("\nWprowadzanie drugiej macierzy");
				if ((y = matrix_in_size_known (a, b, &m2)) != 0)
				{
					err(y);
					break;
				}
				m3 = (double*) calloc(a*b, sizeof (*m3));
				if (m3 == NULL)
				{
					err(NO_MEMORY);
					break;
				}
				subtraction (a, b, m1, m2, m3);
				file_matrix_out (a, b, m3, "Odejmowanie");
				puts ("\nMacierz wynikowa:\n");
				matrix_out (a, b, m3);
				break;

			case 'c':
				puts ("-----MNOZENIE MACIERZY PRZEZ LICZBE-----");
				puts ("Wprowadzanie macierzy");
				if ((y = matrix_in_size_unknown (&a, &b, &m1)) != 0)
				{
					err(y);
					break;
				}
				printf ("Podaj liczbe przez ktora chcesz pomnozyc macierz\nlub x aby wrocic do menu: ");
				while (scanf ("%lf", &v) != 1)
				{
					if ((ch = getchar()) != '\n') _CLEAR_BUFFER;
					if (ch == 'x') break;
					printf ("Podano nieprawidlowa wartosc!\nWprowadz x aby wrocic do menu lub wprowadz wartosc jeszcze raz: ");
				}
				_CLEAR_BUFFER;	
				m3 = (double*) calloc(a*b, sizeof (*m3));
				if (m3 == NULL)
				{
					err(NO_MEMORY);
					break;
				}
				multiplication_number (a, b, v, m1, m3);
				file_matrix_out (a, b, m3, "Mnozenie przez liczbe");
				puts ("\nMacierz wynikowa:\n");
				matrix_out (a, b, m3);
				break;

			case 'd':
				puts ("-----MNOZENIE MACIERZY PRZEZ MACIERZ-----");
				puts ("Wprowadzanie pierwszej macierzy");
				if ((y = matrix_in_size_unknown (&a, &b, &m1)) != 0)
				{
					err(y);
					break;
				}
				puts ("\nWprowadzanie drugiej macierzy");
				if ((y = matrix_in_multip (b, &c, &m2)) != 0)
				{
					err(y);
					break;
				}
				m3 = (double*) calloc(a*c, sizeof (*m3));
				if (m3 == NULL)
				{
					err(NO_MEMORY);
					break;
				}
				multiplication_matrix (a, b, c, m1, m2, m3);
				file_matrix_out (a, c, m3, "Mnozenie przez macierz");
				puts ("\nMacierz wynikowa:\n");
				matrix_out (a, c, m3);
				break;

			case 'e':
				puts ("-----TRANSPONOWANIE MACIERZY-----");
				puts ("Wprowadzanie macierzy");
				if ((y = matrix_in_size_unknown (&a, &b, &m1)) != 0)
				{
					err(y);
					break;
				}
				m3 = (double*) calloc(b*a, sizeof (*m3));
				if (m3 == NULL)
				{
					err(NO_MEMORY);
					break;
				}
				transpose (a, b, m1, m3);
				file_matrix_out (b, a, m3, "Transponowanie");
				puts ("\nMacierz wynikowa:\n");
				matrix_out (b, a, m3);
				break;

			case 'f':
				puts ("-----OBLICZANIE WYZNACZNIKA MACIERZY-----");
				puts ("Wprowadzanie macierzy");
				if ((y = matrix_in_sqr (&a, &m1)) != 0)
				{
					err(y);
					break;
				}
				printf ("Wyznacznik macierzy jest rowny %.6lf\n", determinant (a, m1));
				break;

			case 'g':
				puts ("-----WYZNACZANIE MACIERZY DOPELNIEN ALGEBRAICZNYCH-----");
				puts ("Wprowadzanie macierzy");
				if ((y = matrix_in_sqr (&a, &m1)) != 0)
				{
					err(y);
					break;
				}
				m3 = (double*) calloc(a*a, sizeof (*m3));
				if (m3 == NULL)
				{	
					err(NO_MEMORY);
					break;
				}
				cofactor_matrix (a, m1, m3);
				file_matrix_out (a, a, m3, "Dopelnienia albebraiczne");
				puts ("\nMacierz wynikowa:\n");
				matrix_out (a, a, m3);
				break;

			case 'h':
				puts ("-----WYZNACZANIE MACIERZY ODWROTNEJ-----");
				puts ("Wprowadzanie macierzy");
				if ((y = matrix_in_sqr (&a, &m1)) != 0)
				{
					err(y);
					break;
				}
				m3 = (double*) calloc(a*a, sizeof (*m3));
				if (m3 == NULL)
				{	
					err(NO_MEMORY);
					break;
				}	
				if ((inverse_matrix (a, m1, m3)) == DET_ZERO)
				{
					puts ("Wyznacznik macierzy rowny 0, odwrocenie niemozliwe!");
					break;
				}
				file_matrix_out (a, a, m3, "Odwracanie");
				puts ("\nMacierz wynikowa:\n");
				matrix_out (a, a, m3);
				break;

			case 'i':
				puts ("-----MIERZENIE CZASU ODWRACANIA MACIERZY O LOSOWYCH ELEMENTACH-----");
				printf ("Podaj rozmiar macierzy lub x aby wrocic do menu: ");
				if ((y = value_in (&a, S_MAX)) != 0)
				{
					err(y);
					break;
				}
				printf ("Wymagany czas: %.lfs\n", inverse_time(a));
				break;

			case 'j':
				puts ("-----OBLICZANIE SREDNIEJ Z ELEMENTOW MACIERZY-----");
				puts ("Wprowadzanie macierzy");
				if ((y = matrix_in_size_unknown (&a, &b, &m1)) != 0)
				{
					err(y);
					break;
				}
				printf  ("Srednia z elementow macierzy jest rowna %.6lf\n\n", mean (a*b, m1));
				break;

			case 'k':
				puts ("-----OBLICZANIE MEDIANY Z ELEMENTOW MACIERZY-----");
				puts ("Wprowadzanie macierzy");
				if ((y = matrix_in_size_unknown (&a, &b, &m1)) != 0)
				{
					err(y);
					break;
				}
				printf  ("Mediana z elementow macierzy jest rowna %.6lf\n\n", median (a*b, m1));
				break;

			case 'p':
				system ("CLS");
				menu();
				continue;

			default:
				printf ("Podano nieprawidlowy znak! Sprobuj jeszcze raz: ");
				continue;
		}
		free(m1); free(m2); free(m3);
		system ("PAUSE");
		menu ();
	}
	puts ("Do widzenia!");
	system ("PAUSE");
	return 0;
}

void menu (void)
{
	printf ("___________________________________________________________\n\n\n\n"
			"Wybierz, co chcesz zrobic:\n"
			"a: dodawanie macierzy\n"
			"b: odejmowanie macierzy\n"
			"c: mnozenie macierzy przez liczbe\n"
			"d: mnozenie macierzy przez macierz\n"
			"e: transponowanie macierzy \n"
			"f: obliczanie wyznacznika macierzy\n"
			"g; wyznaczanie macierzy dopelnien algebraicznych\n"
			"h: wyznaczanie macierzy odwrotnej\n"
			"i: obliczanie czasu odwracania macierzy o podanym rozmiarze\n"
			"   wypelnionej losowo wygenerowanymi elementami\n"
			"j: srednia arytmetyczna z elementow macierzy\n"
			"k: mediana z elementow macierzy\n"
			"\n"
			"p: wyczysc ekran\n"
			"q: zakoncz program\n\n\n\n\n"
			"Podaj odpowiedni znak: ");
}

//wyswietla odpowiedni komunikat o bledzie
void err (int e)
{
	puts ("\n");
	switch (e)
	{
		case X_LEAVE:
			break;
		case NO_FILE:
			puts ("Blad! Nie odnaleziono pliku.");
			break;
		case NO_MEMORY:
			puts ("Blad! Za malo pamieci.");
			break;
		case WRONG_SIZE:
			puts ("Blad! Niewlasciwy rozmiar macierzy w pliku.");
			break;
		case CATALOG_ERR:
			puts ("Blad! Nie udalo sie otworzyc katalogu.");
			break;
		case EMPTY_CATALOG:
			puts ("Blad! Nie odnaleziono plikow csv w katalogu.");
			break;
		default:
			break;
	}
}

//pobiera adres wartosci ktora ma pobrac i maksymalna wartosc jaka moze ona przyjac, wartosc minimalna domyslnie wynosi 1
int value_in (short int * value, short int lim)
{
	char ch;
	while ((scanf ("%hd", value) != 1) || *value<1 || *value>lim)
	{
		if ((ch = getchar()) != '\n') _CLEAR_BUFFER;
		if (ch == 'x') return X_LEAVE;
		printf ("Podano nieprawidlowa wartosc!\n"
				"Wprowadz x aby wrocic do menu lub wprowadz wartosc jeszcze raz: ");
	}
	_CLEAR_BUFFER;
	return 0;
}

//pobiera wymiary macierzy i jej adres, wypelnia macierz wartosciami wprowadzanymi z klawiatury
int matrix_in (short int a, short int b, double* matrix)
{
	char ch;
	short int i, j;
	puts ("\nWprowadzaj kolejno elementy macierzy.\nx - powrot do menu   r - wprowadzanie poprzedniego elementu.");
	for (i=0; i<a; i++)
	{
		for (j=0; j<b; j++)
		{
			printf ("\nWprowadz element o indeksie: %hd, %hd : ", i+1, j+1);
			while ((scanf("%lf", matrix + i*b + j)) != 1)
			{
				if ((ch = getchar()) != '\n') _CLEAR_BUFFER;
				if (ch == 'x') return X_LEAVE; //zwroc kod bledu - umyslne przerwanie przez uzytkownika
				if (ch == 'r') //wprowadzanie poprzedniego elementu
				{
					if (j>0) //jezeli nie jest to pierwszy wyraz wiersza to zmniejsz numer kolumny o 1
						j--;
					else if (i>0) //w przeciwnym wypadku, jezeli nie jest to pierwszy wiersz, zmniejsz numer wiersza o 1
					{			  //a numer kolumny ustaw na ostatni (szerokosc - 1)
						i--; j=b-1;
					}			  //jezeli jest to pierwszy wiersz i pierwsza kolumna nic nie rob
					printf ("\nWprowadz element o indeksie: %hd, %hd : ", i+1, j+1);
					continue;
				}
				printf ("Podano nieprawidlowa wartosc!\nWprowadz element o indeksie: %hd, %hd : ", i+1, j+1);
			}
			_CLEAR_BUFFER;
		}
	}
	return 0;
}

void file_list (short int *num, int maxnum, char files [][MAX_FILENAME])
{
	DIR *d;
	struct dirent *dir;
	int len, i=0;
	d = opendir("."); //otworz biezacy katalog
	if (d) //jezeli katalog zostal otworzony poprawnie (d jest niezerowe)
	{
		while ((dir = readdir(d)) != NULL) //dopoki uda sie odczytac nazwe pliku w katalogu
    	{
    		len = strlen(dir->d_name); //dlugosc nazwy pliku
			if (strncmp(dir->d_name + len - 4, ".csv", 4) == 0) //korzysta z tego ze d_name to wzkaznik do tablicy zmiennych char, +len-4 oznacza 
			{													//wez wskaznik 4 znaku od konca i dokonaj porownania z lancuchem ".csv"
				sprintf (files[i++], "%s", dir->d_name); //zapisz nazwe do tablicy lancuchow files
			}
		}
		closedir(d);
		*num = i;
	}
	else *num = CATALOG_ERR;
}

int file_matrix_in (short int* ptr_a, short int* ptr_b, double**m)
{
	char buffer [1024], files[MAX_FILELIST][MAX_FILENAME], *value, *line;
	short int a,b,i,j,s, x=-1, mfnum, fnum;
	int er;
	double m_temp[S_MAX][S_MAX], *matrix=NULL;

	file_list (&mfnum, MAX_FILELIST, files);
	if (mfnum == CATALOG_ERR) return CATALOG_ERR; //jezeli nie udalo sie otworzyc katalogu
	if (mfnum == 0) return EMPTY_CATALOG; //jezeli nie znaleziono zadnego pliku csv
	
	puts ("\nLista odnalezionych plikow:");
	for (s=1; s<=mfnum; s++)
	{
		printf ("%3d.%s\n", s, files[s-1]);
	}
	printf ("\nPodaj numer pliku lub x aby wrocic do menu: ");
	if (value_in (&fnum, mfnum) == X_LEAVE) return X_LEAVE;

	FILE *fp = fopen (files [fnum-1], "r"); //otworz w trybie czytania plik o nazwie zapisanej w tablicy files pod podanym indeksem
	if (fp == NULL)
	{
		return NO_FILE;
	}
	while((line=fgets(buffer,sizeof(buffer),fp))!=NULL) //zapisz do tablicy buffer pierwsza linie pliku (wszystko do znaku '\n')
	{
		j=0;
		value = strtok(line, ";"); //zapisz do value wszystko do znaku ';'
		while (value != NULL) 
		{
			m_temp[i][j++] = atof(value); //skonwertuj value na float i zapisz w m_temp, zwieksz j o 1
			value = strtok(NULL,";"); //pobierz nastepny tekst do znaku ';'
		}
		if (x == -1) x=j; //za pierwszym razem przypisz zmiennej x wartosc j (liczba odczytanych wartosci w wierszu)
		else if (x != j) return WRONG_SIZE; //za kazdym nastepnym razem jezeli odczytana zostanie inna liczba wartosci zwroc kod bledu
		i++;
	}
	if ((i>S_MAX) || (j>S_MAX)) return WRONG_SIZE; //jezeli przekroczono maksymalny rozmiar awroc kod bledu
	*ptr_a = i;	*ptr_b = j; //przypisz odczytane wymiary tablicy odpowiednim zmiennym
	matrix = (double*) calloc(i*j, sizeof (*matrix));
	if (matrix == NULL) return NO_MEMORY;
	for (a=0; a<i; a++) //zaalokuj macierz o potrzebnym rozmiarze, wypelnij ja odczytanymi wartosciami
	{
		for (b=0; b<j; b++)
		{
			*(matrix + a*j + b) = m_temp[a][b];
		}
	}
	*m = matrix;
	return 0;
}

//wczytaj macierz o nieznanych wymiarach
int matrix_in_size_unknown (short int*ptr_a, short int*ptr_b, double**m)
{
	char ch;
	int er;
	double *matrix=NULL;
	printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
	while (1)
	{
		if ((ch = getchar()) == '\n') continue;
		_CLEAR_BUFFER;
		if (ch == 'x') return X_LEAVE;
		else if (ch == 'c')
		{
			printf ("Podaj wysokosc macierzy lub x aby wrocic do menu: ");
			if ((er = value_in (ptr_a, S_MAX)) != 0) break;
			printf ("Podaj szerokosc macierzy lub x aby wrocic do menu: ");
			if ((er = value_in (ptr_b, S_MAX)) != 0) break;
			matrix = (double*) calloc((*ptr_a)*(*ptr_b), sizeof (*matrix));
			if (matrix == NULL)	return NO_MEMORY;
			er = matrix_in ((*ptr_a), (*ptr_b), matrix);
			break;
		}
		else if (ch == 'f')
		{
			if ((er = file_matrix_in (ptr_a, ptr_b, &matrix)) != 0)
			{
				err(er);
				puts ("Wyeliminuj blad lub wprowadz macierz recznie.\n");
				printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
				continue;
			}
			break;
		}
		else puts ("Zly znak! sprobuj raz jeszcze.");
	}
	*m = matrix; 
	return er;
}

//wczytaj macierz o znanych wymiarach
int matrix_in_size_known (short int a, short int b, double**m)
{
	char ch;
	short int c=-1,d=-1;
	int er;
	double *matrix=NULL;
	printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
	while (1)
	{
		if ((ch = getchar()) == '\n') continue;
		_CLEAR_BUFFER;
		if (ch == 'x') return X_LEAVE;
		else if (ch == 'c')
		{
			matrix = (double*) calloc(a*b, sizeof (*matrix));
			if (matrix == NULL)	return NO_MEMORY;
			er = matrix_in (a, b, matrix);
			break;
		}
		else if (ch == 'f')
		{
			if ((er = file_matrix_in (&c, &d, &matrix)) != 0)
			{
				err(er);
				puts ("Wyeliminuj blad lub wprowadz macierz recznie.\n");
				printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
				continue;
			}
			else if (er != 0) break;
			if ((c != a) || (d != b)) er = WRONG_SIZE; //jezeli wymiary macierzy odczytanej z pliku sa rozne od podanych zwroc kod bledu
			break;
		}
		else puts ("Zly znak! sprobuj raz jeszcze.");
	}
	*m = matrix; 
	return er;
}

//wczytaj macierz o znanej szerokosci, odpowiada wczytywaniu drugiej macierzy przy mnozeniu macierzy przez macierz
int matrix_in_multip (short int a, short int *ptr_b, double**m)
{
	char ch;
	short int c=-1;
	int er;
	double *matrix=NULL;
	printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
	while (1)
	{
		if ((ch = getchar()) == '\n') continue;
		_CLEAR_BUFFER;
		if (ch == 'x') return X_LEAVE;
		else if (ch == 'c')
		{
			printf ("Wysokosc macierzy jest rowna %d\n", a);
			printf ("Podaj szerokosc macierzy lub x aby wrocic do menu: ");
			if ((er = value_in (ptr_b, S_MAX)) != 0) break;
			matrix = (double*) calloc(a*(*ptr_b), sizeof (*matrix));
			if (matrix == NULL)	return NO_MEMORY;
			er = matrix_in (a, *(ptr_b), matrix);
			break;
		}
		else if (ch == 'f')
		{
			if ((er = file_matrix_in (&c, ptr_b, &matrix)) != 0)
			{
				err(er);
				puts ("Wyeliminuj blad lub wprowadz macierz recznie.\n");
				printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
				continue;;
			}
			else if (er != 0) break;
			if (c != a) er = WRONG_SIZE;
			break;
		}
		else puts ("Zly znak! sprobuj raz jeszcze.");
	}
	*m = matrix; 
	return er;
}

//wczytaj macierz kwadratowa o nieznanym rozmiarze
int matrix_in_sqr (short int* ptr_a, double**m)
{
	char ch;
	short int a,b;
	int er=0;
	double *matrix=NULL;
	printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
	while (1)
	{
		if ((ch = getchar()) == '\n') continue;
		_CLEAR_BUFFER;
		if (ch == 'x') return X_LEAVE;
		else if (ch == 'c')
		{
			printf ("Podaj rozmiar macierzy lub x aby wrocic do menu: ");
			if ((er = value_in (ptr_a, S_MAX)) != 0) break;
			matrix = (double*) calloc((*ptr_a)*(*ptr_a), sizeof (*matrix));
			if (matrix == NULL)	return NO_MEMORY;
			er = matrix_in ((*ptr_a), (*ptr_a), matrix);
			break;
		}
		else if (ch == 'f')
		{
			if ((er = file_matrix_in (&a, &b, &matrix)) != 0)
			{
				err(er);
				puts ("Wyeliminuj blad lub wprowadz macierz recznie.\n");
				printf ("Wprowadz c aby wpisac macierz, f aby wczytac ja z pliku\nlub x aby wrocic do menu: ");
				continue;
			}
			else if (er != 0) break;
			if (a != b) er = WRONG_SIZE;
			else *ptr_a = a;
			break;
		}
		else puts ("Zly znak! Sprobuj raz jeszcze.");
	}
	*m = matrix; 
	return er;
}

//pobiera wymairy macierzy i jej adres, wypisuje macierz na ekranie
void matrix_out (short int a, short int b, const double* matrix)
{
	short int i, j;
	for (i=0; i<a; i++)
	{
		for (j=0; j<b; j++)
		{
			printf ("%8.2lf ", *(matrix + i*b + j));
		}
		printf ("\n\n");
	}
}

//tworzy plik csv i zapisuje w nim macierz
int file_matrix_out (short int a, short int b, const double* matrix, const char* task)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char filename [60];
	short int i,j;
	FILE * fp;

	sprintf (filename, "%.2d-%.2d-%.4d %.2d-%.2d-%.2d %s.csv", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, task);

	fp = fopen(filename,"a");
	if (fp == NULL)
    {
        return NO_FILE;
    }
	for (i=0; i<a; i++)
	{
		for (j=0; j<b-1; j++)
		{
			fprintf (fp, "%lf;", *(matrix + i*b + j)); //dla wszystkich wartosci poza ostatnia po liczbie postaw znak ';'
		}
		fprintf (fp, "%lf\n", *(matrix + i*b + j)); //dla ostatniej wartosci po liczbie postaw znak '\n'
	}
	fclose (fp);
	return 0;
}

//pobiera adres macierzy wejsciowej i wyjsciowej oraz ich wymiary, dodaje je do siebie i zapisuje w macierzy wynikowej
void addition (short int a, short int b, const double* tab1, const double* tab2, double* tab3)
{
	short int i,j;
	for (i=0; i<a; i++)
	{
		for (j=0; j<b; j++)
		{
			*(tab3 + i*b + j) = *(tab1 + i*b + j) + *(tab2 + i*b + j);
		}
	}
}

//pobiera adres macierzy wejsciowej i wyjsciowej oraz ich wymiary, odejmuje je od siebie i zapisuje w macierzy wynikowej
void subtraction (short int a, short int b, const double* matrix1, const double* matrix2, double* matrix3)
{
	short int i,j;
	for (i=0; i<a; i++)
	{
		for (j=0; j<b; j++)
		{
			*(matrix3 + i*b + j) = *(matrix1 + i*b + j) - *(matrix2 + i*b + j);
		}
	}
}

//pobiera wymiary i adres macierzy oraz liczbe przez ktora ja mnozy, wynik zapisuje w macierzy wynikowej
void multiplication_number (short int a, short int b, double num, const double* matrix_in, double* matrix_out)
{
	short int i,j;
	for (i=0; i<a; i++)
	{
		for (j=0; j<b; j++)
		{
			*(matrix_out + i*b + j) = num * (*(matrix_in + i*b + j));
		}
	}
}

//pobiera adres macierzy wejsciowej i wyjsciowej oraz ich wymiary, 
//UWAGA wymaga podania tablicy wynikowej o WYMAGANYM ROZMIARZE i WYZEROWANEJ!
void multiplication_matrix (short int a, short int b, short int c, const double* matrix1, const double* matrix2, double* matrix3)
{
	short int i,j,k;
	for (i=0; i<a; i++)
	{
		for (j=0; j<c; j++)
		{
			for (k=0; k<b; k++)
				*(matrix3 + i*c + j) += (*(matrix1 + i*b + k)) * (*(matrix2 + k*c + j));
		}
	}
}

// pobiera numer wiersza i kolumny zwraca  -1 ^ (ich sumy)
short int sign (short int line, short int column)
{
	if ((line+column)%2 == 0) return 1;
	else return -1;
}

// pobiera tablice wejsciowa, jej rozmiar oraz nr wiersza i kolumny wzgledem ktorych tworzy minor
// UWAGA rozmiar liczony od 1,  a wiersz i kolumna od 0
// !!zaklada poprawnosc danych!!
void minor (short int n, short int line, short int column, const double* matrix_in, double* matrix_out)
{
	short int i, j;

	for (i=0; i<line; i++)
	{
		for (j=0; j<column; j++)
		{
			*(matrix_out + (n-1)*i + j) = *(matrix_in + n*i + j);
		}
		for ( ; j<n-1; j++)
		{
			*(matrix_out + (n-1)*i + j) = *(matrix_in + n*i + j+1);
		}
	}
	for ( ; i<n-1; i++)
	{
		for (j=0; j<column; j++)
		{
			*(matrix_out + (n-1)*i + j) = *(matrix_in + n*(i+1) + j);
		}
		for ( ; j<n-1; j++)
		{
			*(matrix_out + (n-1)*i + j) = *(matrix_in + n*(i+1) + j+1);
		}
	}
}

// pobiera adres macierz i jej rozmiar i oblicza jej wyznacznik metoda la place'a,
double determinant (short int n, const double* matrix_in)
{
	short int i=0, j;
	double d=0, matrix_minor[n-1][n-1];

	if (n == 1)
		d = *matrix_in; //jezeli rozmiar macierzy jest rowny to wyznacznik macierzy jest rowny jej jedynemu elementowi
	else //jezeli rozmiar macierzy jest wiekszy od 1 obliczanie wyznacznika schematem la'place'a
	{
		for (j=0; j<n; j++)
		{
			minor (n, i, j, matrix_in, *matrix_minor); //utworz minor wzgledem elemntu i j
			if (*(matrix_in + n*i + j)) //jezeli element macierzy jest rowny 0, mozna przejsc od razu do nastepnego elementu
			{
				d += *(matrix_in + n*i + j) * sign(i,j) * determinant(n-1, *matrix_minor);
			}
		}
	}
	return d;
}

//pobiera adres tablicy wejsciowej i wyjsciowej oraz ich rozmiar
//tworzy macierz dopelnien algebraicznych
void cofactor_matrix (short int n, const double* matrix_in, double* matrix_out)
{
	short int i,j;
	double matrix_minor [n-1][n-1];
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			minor (n, i, j, matrix_in, *matrix_minor);
			*(matrix_out + n*i + j) = sign(i,j) * determinant(n-1, *matrix_minor);
		}
	}
}

//pobiera adres tablicy wejciowej i wyjsciowej oraz !!UWAGA!! liczbe wierszy i kolumn PIERWSZEJ z nich
//tworzy macierz transponowana
//UWAGA pamietac o zamianie wymiarow przy korzystaniu z wyjsciowej
void transpose (short int a, short int b, const double* matrix_in, double* matrix_out)
{
	short int i,j;
	for (i=0; i<b; i++)
	{
		for (j=0; j<a; j++)
		{
			*(matrix_out + i*a + j) = *(matrix_in + j*b + i);
		}
	}
}

//pobiera adres tablicy wejsciowej i wyjsciowej oraz ich rozmiar, wyznacza macierz odwrotna
int inverse_matrix (short int n, const double* matrix_in, double* matrix_out)
{
	short int i,j;
	double d, m1 [n][n], m2 [n][n];

	if ((d = determinant(n, matrix_in)) == 0)
		return DET_ZERO;
	
	cofactor_matrix (n, matrix_in, *m1); //tworzy macierz doplenien albebraicznych
	transpose (n, n, *m1, *m2); //macierz dolaczona (transponowana macierz dopelnien)
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			*(matrix_out + n*i + j) = m2[i][j]/d;
		}
	}
	return 0;
}

//tworzy macierz kwadratowa o danym rozmiarze wypelniona losowymi elementami, nastepnie mierzy czas jej odwrocenia
double inverse_time (short int n)
{
	short int i,j;
	double m1 [n][n], m2 [n][n];
	time_t start, end;
	
	srand(time(NULL));
	do
	{
		for (i=0; i<n; i++)
		{
			for (j=0; j<n; j++)
			{
				m1 [i][j] = (double)rand(); //wypelnia tablice losowymi wartosciami
			}
		}
	}	while (determinant (n, *m1) == 0); //sprawdza czy wyznacznik utworzonej tablicy jest rozny od zera

	time (&start);
	inverse_matrix (n, *m1, *m2);
	time (&end);
	return difftime (end, start);
}

//pobiera LACZNA liczbe elementow macierzy oraz jej adres
//zwraca srednia arytmetyczna
double mean (short int size, const double* tab)
{
	short int i;
	double sum=0;
	for (i=0; i<size; i++)
		sum += *(tab + i);
	return sum/size;
}

//quicksort, pobiera adres tablicy oraz indeksy elemntow pomiedzy ktorymi wykonuje sortowanie
void quicksort (double* tab, short int left, short int right)
{
	short int i = left, j = right;
	double t, mid = *(tab+((left+right)/2)); //srodkowy wyraz tablicy wartoscia podzialu tablicy
	while (1)
	{
		while (*(tab+i) < mid) i++; //idac od lewej znajdz element nie mniejszy ed elementu podzialu
		while (*(tab+j) > mid) j--; //idac od prawej znajdz element nie wiekszy od elementu podzialu
		if (i <= j)
		{
			t = *(tab+i);
			*(tab+i) = *(tab+j);
			*(tab+j) = t;
			i++; j--;
		}
		else break; //petla nieskonczona, opuszczana w momencie gdy wymina sie indeksy i j
	}
	if (left < j) quicksort (tab, left, j); //posortuj lewa czesc
	if (right > i) quicksort (tab, i, right); //posortuj prawa czesc
}

//pobiera LACZNA liczbe elementow macierzy oraz jej adres
//zwraca mediane
double median (short int size, const double* tab)
{
	short int i;
	double tab_sort [size];
	for (i=0; i<size; i++)
	{
		*(tab_sort+i) = *(tab+i); //kopiuje tablice wejsciowa aby zachowac ja niezmieniona
	}
	quicksort (tab_sort, 0, size-1);
	return (size % 2) ? tab_sort[size/2] : (tab_sort[size/2 - 1] + tab_sort[size/2]) /2 ;
	//dla nieparzystej liczby elementow zwraca wartosc srodkowego, dla parzystej srednia arytmetyczna srodkowych wartosci
}

