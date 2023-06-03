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

// ��������� ���������� ������ ������ � ����� ������, ����������� �� 32-������ �������
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
    fread(&head_file, sizeof(head_file), 1, f); // ������ ���������
    int width = head_file.biwidth; // ������
    int height = head_file.biheight; // ������
    fread(palitra, sizeof(palitra), 1, f); // ��������� �������
    for (int i = 0; i < 16; i++) // ������������� �������
        setpalette(i, RGB(palitra[i][2], palitra[i][1], palitra[i][0]));
    int offset = Offset(width / 2);
    byte c, c1, c2;
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width / 2; j++) {
            fread(&c, 1, 1, f); // ��������� ���� ���� �������� � ����� �����
            c1 = c >> 4; // �������� ���� ������� �������
            putpixel(j * 2, i, c1); // ���������� ������ ������� � ����
            c2 = c & 0x0F; // �������� ���� ������� �������
            putpixel(j * 2 + 1, i, c2); // ���������� ������ ������� � ����
        }
        fseek(f, offset, SEEK_CUR); // ���������� ������ ����� � ����� ������
    }
    fclose(f);
}

