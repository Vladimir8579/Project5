#define MAXCOLOR16

#include "wingraph.h"

struct head {
    short bftype;
    long  bfsize;
    short rez1, rez2;
    long  bfoffbits;
    long  bisize;
    long  biwidth;
    long  biheight;
    short biplanes;
    short bibitcount;
    long  bicompression;
    long  bisizeimage;
    long  bix;
    long  biy;
    long  biclrused;
    long  biclrimp;
} head_file;

unsigned char palitra[16][4];

// Вычисляет количество пустых байтов в конце строки, выровненной по 32-битной границе
int Offset(int width)
{
    int offset = 0;
    while (width % 4 != 0) {
        width++;
        offset++;
    }
    return offset;
}

void main()
{
    resize(800, 600);
    FILE* f;
    //  f = fopen("_Carib16.bmp", "rb");
    f = fopen("_Carib16.bmp", "rb");
    fread(&head_file, sizeof(head_file), 1, f); // Читаем заголовок
    int width = head_file.biwidth; // Ширина
    int height = head_file.biheight; // Высота
    fread(palitra, sizeof(palitra), 1, f); // Считываем палитру
    for (int i = 0; i < 16; i++) // Устанавливаем палитру
        setpalette(i, RGB(palitra[i][2], palitra[i][1], palitra[i][0]));
    int offset = Offset(width / 2);
    byte c, c1, c2;
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width / 2; j++) {
            fread(&c, 1, 1, f); // Считываем цвет двух пикселей в одном байте
            c1 = c >> 4; // Выделяем цвет первого пикселя
            putpixel(j * 2, i, c1); // Отображаем первый пиксель в окне
            c2 = c & 0x0F; // Выделяем цвет второго пикселя
            putpixel(j * 2 + 1, i, c2); // Отображаем второй пиксель в окне
        }
        fseek(f, offset, SEEK_CUR); // Пропускаем пустые байты в конце строки
    }
    fclose(f);
}

