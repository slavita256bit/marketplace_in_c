#include "io.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <stdio_ext.h>
#include <termios.h>
#include <unistd.h>
#endif

FILE* open_file(char *filename, bool binary, bool write_mode, bool exit_on_fail)
{
    FILE* file = fopen(filename, (binary ? (write_mode ? "wb" : "rb") : (write_mode ? "w" : "r")));
    
    if (file == NULL) 
    {
        printf("Невозможно открыть файл %s!\n", filename);
        if (exit_on_fail) exit(0);
    }

    return file;
}

int read_int_range(int from, int to)
{
    int x;
    do
    {
        printf("Введите число (от %d, до %d): ", from, to);
        x = read_int(stdin, false);
    } while (x < from || x > to);
    return x;
}

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

void read_string(char* str, FILE* file, bool until_ln)
{
    flush_buffer(file);
    fscanf(file, (until_ln ? "%*[^\n]" : "%s"), str);
}


void flush_buffer(FILE* file)
{
    if (file == stdin)
    {
#ifdef _WIN32
        rewind(stdin);
#else
        __fpurge(stdin); // Очищает внутренний буфер C (остатки от scanf/fgets)
        tcflush(STDIN_FILENO, TCIFLUSH); // Очищает буфер терминала ОС (нажатия клавиш)
#endif
    }
}


void print_n_times(int n, char c)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
