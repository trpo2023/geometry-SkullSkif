#include <libgeometry/parser.h>

#define maxvalue 100
#define maxstr 255


void checkFile(FILE* data)
{
    if (data == NULL) {
        printf("Файл с входными данными не обнаружен.\n");
        exit(1);
    }
}

int objectsCount(char* filename) //  кол-во строк в файле
{
    FILE* data;
    int count = 0;
    data = fopen(filename, "r");
    while (!feof(data)) {
        if (fgetc(data) == '\n')
            count++;
    }
    count++; 
    fclose(data);
    return count;
}

void checkName(char* strObject, int* pos, int strcount)
{
    char strTemplateCircle[maxstr] = {"circle(0 0, 1.5)"};
    char strName[maxstr];
    while (((strObject[*pos] >= 'a') && (strObject[*pos] <= 'z'))
           || ((strObject[*pos] >= 'A') && (strObject[*pos] <= 'Z'))) {
        strName[*pos] = tolower(strObject[*pos]);
        *pos = *pos + 1;
    }
    char strTemp[] = "circle";
    if (strlen(strName) != strlen(strTemp)) {
        printf("Ошибка в %d строке, неверно введена фигура, ожидалось circle\n",
               strcount + 1);
        exit(1);
    }

    for (int i = 0; i < strlen(strName); i++) {
        if (strName[i] != strTemplateCircle[i]) {
            printf("Ошибка в %d строке в %d символе, неверно введена фигура, "
                   "ожидалось circle\n",
                   strcount,
                   i);
            exit(1);
        }
    }
    *pos = strlen(strName);
}

void checkColumn(char* strObject, int* pos, int strcount)
{
    if (strObject[*pos] != '(') {
        printf("Ошибка в %d строке в 6 символе, ожидалось (", strcount);
        exit(1);
    }
}

void checkPointX(char* strObject, int* pos, circle* Object, int strcount)
{
    *pos = *pos + 1;
    int j = 0;
    char number[maxstr] = {
            'a',
    };
    while (isdigit(strObject[*pos])) {
        number[j] = strObject[*pos];
        j++;
        *pos = *pos + 1;
    }
    Object->coord->x = 5;
    Object->coord->x = atoi(number);
    if (number[0] == 'a') {
        printf("Ошибка в %d строке в координате X, ожидалось целое число",
               strcount);
        exit(1);
    }
}

void checkPointY(char* strObject, int* pos, circle* Object, int strcount)
{
    *pos = *pos + 1;
    int j = 0;
    char number[maxstr] = {
            'a',
    };
    while (strObject[*pos] == ' ')
        *pos = *pos + 1;
    if (!isdigit(strObject[*pos])) {
        printf("Ошибка в %d строке в %d символе, ожидалось целое число",
               strcount,
               *pos);
        exit(1);
    }
    while (isdigit(strObject[*pos])) {
        number[j] = strObject[*pos];
        j++;
        *pos = *pos + 1;
    }
    Object->coord->y = atoi(number);
    if (number[0] == 'a') {
        printf("Ошибка в %d строке в координате Y, ожидалось целое число",
               strcount);
        exit(1);
    }
}

void checkPointRad(char* strObject, int* pos, circle* Object, int strcount)
{
    int j = 0;
    char number[maxstr] = {
            'a',
    };
    while (strObject[*pos] != ',') {
        if (strObject[*pos] == ' ') {
            *pos = *pos + 1;
        } else {
            printf("Ошибка в %d строке в %d символе, ожидалась запятая",
                   strcount,
                   *pos);
            exit(1);
        }
    }
    *pos = *pos + 1;
    while (!isdigit(strObject[*pos])) {
        if (strObject[*pos] != ' ') {
            printf("Ошибка в %d строке в радиусе, ожидалось число с плавающей "
                   "точкой",
                   strcount);
            exit(1);
        } else {
            *pos = *pos + 1;
        }
    }
    while (isdigit(strObject[*pos])) {
        number[j] = strObject[*pos];
        j++;
        *pos = *pos + 1;
    }
    if (strObject[*pos] == '.') {
        number[j] = '.';
        j++;
        *pos = *pos + 1;
        while (isdigit(strObject[*pos])) {
            number[j] = strObject[*pos];
            j++;
            *pos = *pos + 1;
        }
    } else {
        printf("Ошибка в %d строке в радиусе, ожидалось число с плавающей "
               "точкой",
               strcount);
        exit(1);
    }
    Object->rad = atof(number);

    if (number[0] == 'a') {
        printf("Ошибка в %d строке в радиусе, ожидалось число с плавающей "
               "точкой",
               strcount);
        exit(1);
    }
    while (strObject[*pos] != ')')
        if (strObject[*pos] != ' ') {
            printf("Ошибка в %d строке в %d символе, ожидалась )",
                   strcount,
                   *pos);
            exit(1);
        } else
            *pos = *pos + 1;
}

void checkError(char* strObject, int* pos, circle* Object, int strcount)
{
    checkName(strObject, pos, strcount);
    checkColumn(strObject, pos, strcount);
    checkPointX(strObject, pos, Object, strcount);
    checkPointY(strObject, pos, Object, strcount);
    checkPointRad(strObject, pos, Object, strcount);
}

void getObjects(FILE* data, int lines_count, circle* Objects)
{
    char strObject[maxstr] = "";
    int pos = 0;
    int strcount = 0;
    for (int i = 0; i < lines_count; i++) {
        fgets(strObject, maxstr, data); // считываю строку с файла
        Objects[i].coord = (point*)malloc(sizeof(point));
        Objects[i].intersects = (int*)malloc(lines_count * sizeof(int));
        pos = 0;
        checkError(strObject, &pos, &Objects[i], strcount);
        strcpy(Objects[i].string, strObject);
        strcount++;
    }
}

void getParametrs(circle* Objects,int lines_count)
{
    double d = 0;
    for (int i = 0;i<lines_count;i++)
        {
            for (int j = lines_count-1;j>i;j--)
                {
                    d = sqrt(pow(((Objects[j].coord->x)-(Objects[i].coord->x)),2)+pow(((Objects[j].coord->y)-(Objects[i].coord->y)),2)); 
                    Objects[i].intersects[j] = 1;
                    if (d>(Objects[i].rad+Objects[j].rad))
                        Objects[i].intersects[j] = 0;
                    if (d<abs(Objects[i].rad-Objects[j].rad))
                        Objects[i].intersects[j] = 1;
                    if (Objects[i].intersects[j] == 1)
                        Objects[j].intersects[i] = 1;
                }
        }
    for (int i = 0;i<lines_count;i++)
        {
            Objects[i].perimeter = 2 * 3.14 * Objects[i].rad;
            Objects[i].area = 3.14 * pow(Objects[i].rad,2);
        }
}

void writeOutput(circle* Objects,int lines_count)
{
    FILE* out;
    out = fopen("bin/output.txt","w+t");
    for (int i = 0;i<=lines_count-1;i++)
        {
            fprintf(out,"%d. %s",i+1,Objects[i].string);
            if (i==lines_count-1)
                fprintf(out,"\n");
            fprintf(out,"\tperimeter = %.4f\n\tarea = %.4f\n\tintersects:\n",Objects[i].perimeter,Objects[i].area);
                for (int j = 0;j<lines_count;j++)
                    {
                        if (Objects[i].intersects[j])
                            fprintf(out,"\t\t%d. circle\n",j+1);
                    }
            fprintf(out,"\n");
        }
}