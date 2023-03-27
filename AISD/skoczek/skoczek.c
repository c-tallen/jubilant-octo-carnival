#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int wiersz, kolumna;
} pozycja;
int s = 0;


void ruchy_stw();
void wypisz(int **szachownica, int n);
void skoczek(int **szachownica, int n, pozycja p);


pozycja ruchy[8];

int main(void)
{
    pozycja start;
    start.wiersz = 0;
    start.kolumna = 0;
    const int n = 5;
    int **szachownica = malloc(n * sizeof (int *));
    for (int i = 0; i <n; ++i) {
        szachownica[i] = malloc(n * sizeof(int));
    }
    ruchy_stw();
    wypisz(szachownica, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            start.wiersz = i;
            start.kolumna = j;
            skoczek(szachownica, n, start);
        }
    }
    printf("Liczba scieżek: %d\n", s);
    for (int i = 0; i < n; ++i) {
        free(szachownica[i]);
    }
    free(szachownica);
    return 0;
}

void ruchy_stw()
{
    int i = 0;
    for (int j = 0; j < 2; j++)
    {
        for (int k = 0; k < 2; ++k) {
            ruchy[i].wiersz = j % 2? 2 : -2;
            ruchy[i].kolumna = k % 2? 1 : -1;
            ruchy[i + 4].wiersz = j % 2? 1 : -1;
            ruchy[i + 4].kolumna = k % 2? 2 : -2;
            i++;
        }
    }
}

void wypisz(int **szachownica, int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%-3d", szachownica[i][j]);
        }
        printf("\n");
    }
}


void skoczek(int **szachownica, int n, pozycja p)
{
    // Ustal gdzie skoczek może się ruszyć
    int mp = 0;
    pozycja nowa;
    for (int i = 0; i < 8; ++i) {
        nowa.kolumna = p.kolumna + ruchy[i].kolumna;
        nowa.wiersz = p.wiersz + ruchy[i].wiersz;
        if (nowa.kolumna < n && nowa.wiersz < n && nowa.kolumna >= 0 && nowa.wiersz >= 0)
        {
            if (szachownica[nowa.kolumna][nowa.wiersz] == 0) {
                szachownica[p.kolumna][p.wiersz] = 1;
//                wypisz(szachownica, n);
//                printf("\n");
                skoczek(szachownica, n, nowa);
                szachownica[p.kolumna][p.wiersz] = 0;
            }
        }
    }
    int flag = 0;
    szachownica[p.kolumna][p.wiersz] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (szachownica[i][j] == 0) {
                flag = 1;
                break;
            }
        }
    }
    szachownica[p.kolumna][p.wiersz] = 0;
    if (flag == 0)
        s++;
}
