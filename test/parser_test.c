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