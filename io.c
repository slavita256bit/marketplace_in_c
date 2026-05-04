#include "io.h"

int read_int(FILE* file, bool binary)
{
    flush_buffer(file);
    int x;
    if (binary)
        fread(&x, sizeof(int), 1, file);
    else
        fscanf(file, "%d", &x);
    return x;
}

void print_int(int x, FILE* file, bool binary)
{
    if (binary)
        fwrite(&x, sizeof(int), 1, file);
    else
        fprintf(file, "%d", x);
}

void read_string(char* str, FILE* file, bool until_ln)
{
    flush_buffer(file);
    fscanf(file, (until_ln ? "%*[^\n]" : "%s"), str);
}

void flush_buffer(FILE* file)
{
    if (file == stdin)
        rewind(file);
}
