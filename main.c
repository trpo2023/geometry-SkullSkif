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

int objectsCount(char* filename) //  кол-во строк в файле
{
    FILE *data;
    int count = 0;
    data = fopen(filename,"r");
    while (! feof(data))
    {
        if (fgetc(data) == '\n')
            count++;
    }
    count++;
    fclose(data);
    return count;
}

void checkName(char* strObject, int* pos,int strcount)
{
    char strTemplateCircle[maxstr] = {"circle(0 0, 1.5)"};
    char strName[maxstr];
    while (((strObject[*pos]>='a') && (strObject[*pos]<='z')  ) || ((strObject[*pos]>='A') && (strObject[*pos]<='Z')))
    {
        strName[*pos] = tolower(strObject[*pos]);
        *pos = *pos + 1;
    }
    char strTemp[] = "circle";
    if (strlen(strName)!=strlen(strTemp))
        {
            printf("Ошибка в %d строке, неверно введена фигура, ожидалось circle\n",strcount+1);
            exit(1);
        }
    
    for (int i = 0;i<strlen(strName);i++)
    {
        if (strName[i]!=strTemplateCircle[i])
        {
            printf("Ошибка в %d строке в %d символе, неверно введена фигура, ожидалось circle\n",strcount, i);
            exit(1);
        }
    }
    *pos = strlen(strName);
}

void checkColumn(char* strObject,int *pos,int strcount)
{
    if (strObject[*pos]!='(')
    {
        printf("Ошибка в %d строке в 6 символе, ожидалось (",strcount);
        exit(1);
    }
}

void checkPointX(char* strObject,int *pos, circle* Object,int strcount)
{
    *pos = *pos + 1;
    int j = 0;
    char number[maxstr] = {'a',};
    while (isdigit(strObject[*pos]))
    {
        number[j]=strObject[*pos];
        j++;*pos = *pos + 1;
    }
    Object->coord->x = 5;
    Object->coord->x= atoi(number);
    if (number[0]=='a')
    {
        printf("Ошибка в %d строке в координате X, ожидалось целое число",strcount);
        exit(1);

    }
}

void checkPointY(char* strObject, int* pos, circle* Object,int strcount )
{
    *pos = *pos + 1;
    int j = 0;
    char number[maxstr] = {'a',};
    while (strObject[*pos]==' ')
        *pos = *pos + 1;
    if (!isdigit(strObject[*pos]))
        {
            printf("Ошибка в %d строке в %d символе, ожидалось целое число",strcount,*pos);
            exit(1);
        }
    while (isdigit(strObject[*pos]))
    {
        number[j]=strObject[*pos];
        j++;*pos = *pos + 1;
    }
    Object->coord->y= atoi(number);
    if (number[0]=='a')
    {
        printf("Ошибка в %d строке в координате Y, ожидалось целое число",strcount);
        exit(1);
    }
}

void checkPointRad(char* strObject,int* pos, circle* Object,int strcount)
{
    int j = 0;
    char number[maxstr] = {'a',};
    while (strObject[*pos]!=',')
        {
            if (strObject[*pos]==' ')
            {
                *pos = *pos + 1;
            } else
                {
                    printf("Ошибка в %d строке в %d символе, ожидалась запятая",strcount,*pos);
                    exit(1);
                }
        }
    *pos = *pos + 1;
    while (!isdigit(strObject[*pos]))
        {
            if (strObject[*pos]!=' ')
                {
                printf("Ошибка в %d строке в радиусе, ожидалось число с плавающей точкой",strcount);
                exit(1);
                } else
                {
                    *pos = *pos + 1;
                }

        }
    while (isdigit(strObject[*pos]))
        {
            number[j]=strObject[*pos];
            j++;*pos = *pos + 1;
        }
    if (strObject[*pos]=='.')
    {
        number[j]='.';
        j++;
        *pos = *pos + 1;
        while (isdigit(strObject[*pos]))
        {
        number[j]=strObject[*pos];
        j++;*pos = *pos + 1;
        }
    } else
        {
        printf("Ошибка в %d строке в радиусе, ожидалось число с плавающей точкой",strcount);
        exit(1);
        }
    Object->rad=atof(number);

    if (number[0]=='a')
    {
        printf("Ошибка в %d строке в радиусе, ожидалось число с плавающей точкой",strcount);
        exit(1);
    }
    while (strObject[*pos]!=')')
        if (strObject[*pos]!=' ')
        {
            printf("Ошибка в %d строке в %d символе, ожидалась )",strcount,*pos);
            exit(1);
        } else *pos = *pos + 1;

}


void checkError(char* strObject,int* pos, circle* Object, int strcount)
{
    checkName(strObject, pos,strcount);
    checkColumn(strObject,pos,strcount);
    checkPointX(strObject,pos, Object,strcount);
    checkPointY(strObject,pos, Object,strcount);
    checkPointRad(strObject,pos, Object,strcount);
}

void getObjects(FILE* data, int lines_count, circle* Objects)
{
    char strObject[maxstr] = "";
    int pos = 0; 
    int strcount = 0;
    for (int i=0;i<lines_count;i++)
    {    
        fgets(strObject,maxstr,data); // считываю строку с файла    
        Objects[i].coord = (point*)malloc(sizeof(point));
        Objects[i].intersects = (int*)malloc(lines_count * sizeof(int));
        pos = 0;
        checkError(strObject,&pos, &Objects[i],strcount);
        strcpy(Objects[i].string, strObject);
        strcount++;
    }

}

int main()
{
    char filename[maxvalue] = "input.txt";
    FILE *data;
    data = fopen(filename,"r");
    checkFile(data);
    int lines_count = 0;
    lines_count = objectsCount(filename);
    circle* Objects = (circle*) malloc(lines_count * sizeof(circle));
    getObjects(data,lines_count, Objects);
    for (int i=0;i<lines_count;i++)
        printf("%s\n",Objects[i].string)
    return 0;
}