#include <ctest.h>
#include <libgeometry/parser.h>



CTEST(TEST_file, file_input)
{
   // char expected_file[] = "bin/input.txt";
    int result;
    FILE* expected = fopen("bin/input.txt","r");
    if (expected == NULL)
        result = 0;
    else result = 1;
    ASSERT_EQUAL(1,result);
    fclose(expected);
}

CTEST(TEST_file, is_file_empty)
{
    FILE* data = fopen("bin/input.txt","r");
    ASSERT_NOT_EQUAL(EOF,fgetc(data));
    fclose(data);


}

CTEST(TEST_data, getstring)
{
    char filename[] = "bin/input.txt";
    FILE *data;
    data = fopen(filename,"r");    
    int lines_count = 0;
    lines_count = objectsCount(filename);
    circle* Objects = (circle*) malloc(lines_count * sizeof(circle));
    getObjects(data,lines_count, Objects);
    getParametrs(Objects,lines_count);
    writeOutput(Objects,lines_count);
    char str[maxstr];
    fseek(data,0,0);
    for (int i = 0;i<lines_count;i++)
        {
            fgets(str,maxstr,data);
            ASSERT_STR(str, Objects[i].string);
        }
    for (int i=0;i<lines_count;i++)
        {
            free(Objects[i].intersects);
            free(Objects[i].coord);
        }
    free(Objects);    
    fclose(data);
}