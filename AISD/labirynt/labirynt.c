#include <stdio.h>
#include <stdlib.h>
typedef unsigned char BYTE;

void wypisz_obraz(BYTE **obraz, int width, int height);

int main(void)
{
    char buffer[40];
    FILE *infile = fopen("diag-20x10.pgm", "r");
    FILE *outfile = fopen("out-labirynt.pgm", "w");
    fscanf(infile, "%s", buffer);
    fprintf(outfile, "%s ", buffer);
    fscanf(infile, "%s", buffer);
    fprintf(outfile, "%s ", buffer);
    int width = atoi(buffer);
    fscanf(infile, "%s", buffer);
    fprintf(outfile, "%s ", buffer);
    int height = atoi(buffer);
    fscanf(infile, "%s", buffer);
    fprintf(outfile, "%s ", buffer);
    BYTE **obraz = malloc(height * sizeof(BYTE *));
    for (int i = 0; i < height; i++)
    {
        obraz[i] = malloc(width * sizeof(BYTE));
    }
    
    for (size_t i = 0; i < height; i++)
    {
        fread(obraz[i], sizeof(BYTE), width, infile);
    }
    wypisz_obraz(obraz, width, height);
    for (size_t i = 0; i < height; i++)
    {
        fwrite(obraz[i], sizeof(BYTE), width, outfile);
    }
    
    
    fclose(infile);
    fclose(outfile);
    return 0;
}

void szukaj_drogi(BYTE **labirynt, int x, int y)
{

}

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
