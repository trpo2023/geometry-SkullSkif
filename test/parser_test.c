#include <ctest.h>
#include <libgeometry/parser.h>

#define CTEST_SEGFAULT
#define CTEST_COLOR_OK

CTEST(TEST_file, file_input)
{
    // char expected_file[] = "bin/input.txt";
    int result;
    FILE* expected = fopen("bin/input.txt", "r");
    if (expected == NULL)
        result = 0;
    else
        result = 1;
    ASSERT_EQUAL(1, result);
    fclose(expected);
}

CTEST(TEST_file, is_file_empty)
{
    FILE* data = fopen("bin/input.txt", "r");
    ASSERT_NOT_EQUAL(EOF, fgetc(data));
    fclose(data);
}

CTEST(TEST_data, getstring)
{
    char filename[] = "bin/input.txt";
    FILE* data;
    data = fopen(filename, "r");
    int lines_count = 0;
    lines_count = objectsCount(filename);
    circle* Objects = (circle*)malloc(lines_count * sizeof(circle));
    getObjects(data, lines_count, Objects);
    getParametrs(Objects, lines_count);
    writeOutput(Objects, lines_count);
    char str[maxstr];
    fseek(data, 0, 0);
    for (int i = 0; i < lines_count; i++) {
        fgets(str, maxstr, data);
        ASSERT_STR(str, Objects[i].string);
    }
    for (int i = 0; i < lines_count; i++) {
        free(Objects[i].intersects);
        free(Objects[i].coord);
    }
    free(Objects);
    fclose(data);
}

CTEST(TEST_data, is_perimetr_positiv)
{
    char filename[] = "bin/input.txt";
    FILE* data;
    data = fopen(filename, "r");
    int lines_count = 0;
    int expected;
    lines_count = objectsCount(filename);
    circle* Objects = (circle*)malloc(lines_count * sizeof(circle));
    getObjects(data, lines_count, Objects);
    getParametrs(Objects, lines_count);
    for (int i = 0; i < lines_count; i++) {
        if (Objects[i].perimeter >= 0)
            expected = 1;
        else
            expected = 0;
        ASSERT_EQUAL(1, expected);
    }
    for (int i = 0; i < lines_count; i++) {
        free(Objects[i].intersects);
        free(Objects[i].coord);
    }
    free(Objects);
    fclose(data);
}

CTEST(TEST_data, is_area_positiv)
{
    char filename[] = "bin/input.txt";
    FILE* data;
    data = fopen(filename, "r");
    int lines_count = 0;
    int expected;
    lines_count = objectsCount(filename);
    circle* Objects = (circle*)malloc(lines_count * sizeof(circle));
    getObjects(data, lines_count, Objects);
    getParametrs(Objects, lines_count);
    for (int i = 0; i < lines_count; i++) {
        if (Objects[i].area >= 0)
            expected = 1;
        else
            expected = 0;
        ASSERT_EQUAL(1, expected);
    }
    for (int i = 0; i < lines_count; i++) {
        free(Objects[i].intersects);
        free(Objects[i].coord);
    }
    free(Objects);
    fclose(data);
}

CTEST(TEST_data, is_name_correct)
{
    char filename[] = "bin/input.txt";
    FILE* data;
    data = fopen(filename, "r");
    char strObject[maxstr];
    fgets(strObject, maxstr, data);
    char strTemplateCircle[maxstr] = {"circle(0 0, 1.5)"};
    char strName[maxstr];
    int g = 0;
    for (int strcount = 0; strcount < objectsCount(filename); strcount++) {
        while (((strObject[g] >= 'a') && (strObject[g] <= 'z'))
               || ((strObject[g] >= 'A') && (strObject[g] <= 'Z'))) {
            strName[g] = tolower(strObject[g]);
            g = g + 1;
        }
        char strTemp[] = "circle";
        if (strlen(strName) != strlen(strTemp)) {
            printf("Ошибка в %d строке, неверно введена фигура, ожидалось "
                   "circle\n",
                   strcount + 1);
            exit(1);
        }

        for (int i = 0; i < strlen(strName); i++) {
            if (strName[i] != strTemplateCircle[i]) {
                printf("Ошибка в %d строке в %d символе, неверно введена "
                       "фигура, "
                       "ожидалось circle\n",
                       strcount,
                       i);
                exit(1);
            }
        }
        ASSERT_STR(strTemp, strName);
    }
}
CTEST(TEST_data, is_circle_lower)
{
    char unexpected[maxstr] = "CirClE";
    char expected[maxstr] = "circle";
    char strName[maxstr];
    int i = 0;
    while (((unexpected[i] >= 'a') && (unexpected[i] <= 'z'))
           || ((unexpected[i] >= 'A') && (unexpected[i] <= 'Z'))) {
        strName[i] = tolower(unexpected[i]);
        i++;
    }
    ASSERT_STR(expected, strName);
}

CTEST(TEST_data, is_number_in_y_correct)
{
    int i = 0;
    int j = 0;
    int y = 0;
    char expected[maxstr] = " 0, 4.0)";
    char number[maxstr] = {
            'a',
    };
    while (expected[i] == ' ')
        i = i + 1;
    if (!isdigit(expected[i])) {
        exit(1);
    }
    while (isdigit(expected[i])) {
        number[j] = expected[i];
        j++;
        i = i + 1;
    }
    y = atoi(number);
    if (number[0] == 'a') {
        exit(1);
    }
    ASSERT_EQUAL(0, y);
}

CTEST(TEST_data, is_number_in_x_correct)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int expectedint = 4;
    char expected[maxstr] = "4 0, 4.0)";
    char number[maxstr] = {
            'a',
    };
    while (isdigit(expected[i])) {
        number[j] = expected[i];
        j++;
        i = i + 1;
    }
    x = 5;
    x = atoi(number);
    ASSERT_EQUAL(expectedint, x);
}
