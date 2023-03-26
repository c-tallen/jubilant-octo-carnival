#include <stdio.h>
#include <stdlib.h>
#define PUSTE (-1)

void rysuj(int *szachownica, int n);
void szukaj(int *szachownica, int n, int wiersz);

int main(void)
{
    const int n = 5;
    int szachownica[n];
    for (size_t i = 0; i < n; i++)
    {
        /*PUSTE to every szachownica[i]*/
        szachownica[i] = PUSTE;
    }
    
    rysuj(szachownica, n);
    printf("\n");
    szukaj(szachownica,n, 0);
    return 0;
}   

void rysuj(int *szachownica, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (szachownica[j] == i)
            {
                printf("H");

            }
            else if ((i + j) % 2)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

void zdejmij(int *szachownica, int n, int wiersz)
{
    for (int i =0; i < n; i++)
    {
        if (szachownica[i] == wiersz)
            szachownica[i] = PUSTE;
    }
}

void szukaj(int *szachownica, int n, int wiersz)
{
    if (n == wiersz)
    {
        printf("--------------------------------------------------\n");
        rysuj(szachownica, n);
        printf("-----------------------------------------------------\n");
        return;
    }
    int atakuje;
    for(int i = 0; i < n; i++)
    {
        atakuje = 0;
        if (szachownica[i] != PUSTE)
        {
            for (int j = 0; j < n; j++)
            {
                if (szachownica[j] != PUSTE && abs(i - j) == abs(szachownica[j] - wiersz))
                {
                    atakuje = 1;
                }
            }
        }
        if (!atakuje)
        {
            szachownica[i] = wiersz;
            rysuj(szachownica, n);
            printf("\n");
            szukaj(szachownica, n, wiersz + 1);
            //zdejmij(szachownica, n, wiersz);
        }
    }
}
