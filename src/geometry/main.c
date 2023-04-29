#include <libgeometry/parser.h>

int main()
{
    char filename[maxvalue] = "bin/input.txt";
    FILE* data;
    data = fopen(filename, "r");
    checkFile(data);
    int lines_count = 0;
    lines_count = objectsCount(filename);
    circle* Objects = (circle*)malloc(lines_count * sizeof(circle));
    getObjects(data, lines_count, Objects);
    getParametrs(Objects, lines_count);
    writeOutput(Objects, lines_count);
    for (int i = 0; i < lines_count; i++) {
        free(Objects[i].intersects);
        free(Objects[i].coord);
    }
    free(Objects);
    fclose(data);
    return 0;
}