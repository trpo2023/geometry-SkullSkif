#pragma once
#include <stdio.h>
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

void checkFile(FILE* data);

int objectsCount(char* filename);

void checkName(char* strObject, int* pos,int strcount);

void checkColumn(char* strObject,int *pos,int strcount);

void checkPointX(char* strObject,int *pos, circle* Object,int strcount);

void checkPointY(char* strObject, int* pos, circle* Object,int strcount);

void checkPointRad(char* strObject,int* pos, circle* Object,int strcount);

void checkError(char* strObject,int* pos, circle* Object, int strcount);

void getObjects(FILE* data, int lines_count, circle* Objects);

void getParametrs(circle* Objects,int lines_count);

void writeOutput(circle* Objects,int lines_count);