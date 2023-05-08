#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

struct Obrazek
{
    int width;
    int height;
    int **pixels;
};

struct klaster
{
    int color;
    int size;
};

int main(int argc, char **argv)
{
    string buffer;
    ifstream infile(argv[1]);
    getline(infile, buffer);
    getline(infile, buffer);
    Obrazek obraz;
    obraz.height = stod(buffer);
    getline(infile, buffer);
    obraz.width = stod(buffer);
    obraz.pixels = new int *[obraz.width];
    for (int i = 0; i < obraz.width; i++)
    {
        obraz.pixels[i] = new int[obraz.height];
    }
}