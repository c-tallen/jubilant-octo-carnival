#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

void wypisz_obraz(BYTE **obraz, int width, int height);
void zapisz_labirynt(BYTE **labirynt, BYTE **rozwiazanie, int width, int height);
int szukaj_drogi(BYTE **labirynt, int x, int y, int width, int height, BYTE **rozwiazanie);
int ruchy[4][2] = {{0, 1},{1, 0},{0, -1}, {-1, 0}};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Użycie: ./labirynt INFILE_labirynt\n");
        return 1;
    }
    char buffer[40];
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Nie można otworzyć pliku.\n");
        return 1;
    }
    fscanf(infile, "%s", buffer);
    fscanf(infile, "%s", buffer);
    int width = atoi(buffer);
    fscanf(infile, "%s", buffer);
    int height = atoi(buffer);
    fscanf(infile, "%s ", buffer);
    BYTE **obraz = malloc(height * sizeof(BYTE *)), **rozwiazanie = malloc(height * sizeof(BYTE *));
    for (int i = 0; i < height; i++)
    {
        obraz[i] = malloc(width * sizeof(BYTE));
        rozwiazanie[i] = malloc(width * sizeof(BYTE));
    }
    
    for (size_t i = 0; i < height; i++)
    {
        fread(obraz[i], sizeof(BYTE), width, infile);
    }

    // Szukamy bialego pola w pierwszym wierszu lub kolumnie labiryntu
    int x_poczatek, y_poczatek;
    for (int i = 1; i < width; i++)
    {
        if (obraz[0][i] == 255)
        {
            x_poczatek = i;
            y_poczatek = 0;
            break;
        }
    }
    for (int i = 0; i < height; i++)
    {
        if (obraz[i][0] == 255)
        {
            x_poczatek = 0;
            y_poczatek = i;
            break;
        }
    }
    
    int droga = szukaj_drogi(obraz, x_poczatek, y_poczatek, width, height, rozwiazanie);
    if (droga)
    {
        char outfile_name[40]; 
        sprintf(outfile_name, "%s-solved.pgm", argv[1]);
        FILE *outfile = fopen(outfile_name, "w");
        fprintf(outfile, "P5\n%i %i\n255\n", width, height);
        for (int i = 0; i < height; i++)
        {
            fwrite(rozwiazanie[i], sizeof(BYTE), width, outfile);
        }
        fclose(outfile);
    }
    else
    {
        printf("Nie znaleziono ścieżki w labirynice.\n");
    }
    fclose(infile);
    for (int i = 0; i < height; i++)
    {
        free(rozwiazanie[i]);
        free(obraz[i]);
    }
    free(rozwiazanie);
    free(obraz);
    return !droga;
}

// Zapisuje labirynt w tablicy rozwiązanie
void zapisz_labirynt(BYTE **labirynt, BYTE **rozwiazanie, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        memcpy(rozwiazanie[i], labirynt[i], width * sizeof(BYTE));
    }
    
}


// Szuka ścieżki w labiryncie i zwraca 1 jeśli znalezionat
int szukaj_drogi(BYTE **labirynt, int x, int y, int width, int height, BYTE **rozwiazanie)
{
    int flag = 0;
    // Jeśli zna
    if (x == width - 1 || y == height - 1)
    {
        labirynt[y][x] = 128;
        zapisz_labirynt(labirynt, rozwiazanie, width, height);
        labirynt[y][x] = 255;
        return 1;
    }
    int x_nowe, y_nowe;
    for (int i = 0; i < 4; i++)
    {
        // Jeśli rozwiązanie znalezione, zakończ pętle
        if (flag) break;
        // Następna pozycja
        x_nowe = x + ruchy[i][0];
        y_nowe = y + ruchy[i][1];
        // Sprawdzamy czy pozycja nie jest zajęta lub poza labiryntem
        if (x_nowe >= 0 && y_nowe >= 0 && x_nowe < width && y_nowe < height && labirynt[y_nowe][x_nowe] == 255)
        {
            labirynt[y][x] = 128;
            flag = szukaj_drogi(labirynt, x_nowe, y_nowe, width, height, rozwiazanie);
            labirynt[y][x] = 255;
        }
    }
    return flag;
}

/*Funkcja wypisuje labirynt do terminala... tylko do debugowania*/
void wypisz_obraz(BYTE **obraz, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%-3d ", obraz[i][j]);
        }
        printf("\n");
    }
    
}
