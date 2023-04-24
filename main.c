#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define maxvalue 100
#define maxstr 255

struct Point
{
    int x;
    int y;
};
typedef struct Point point;

struct Circle
{
    char string[maxstr];
    double rad;
    point* coord;
    double perimeter;
    double area;
    int* intersects;
};
typedef struct Circle circle;

void checkFile(FILE* data)
{
    if (data == NULL)
    {
    printf("Файл с входными данными не обнаружен.\n");
    exit(1);
    }
}

int main()
{
    char filename[maxvalue] = "input.txt";
    FILE *data;
    data = fopen(filename,"r");
    checkFile(data);

    return 0;
}