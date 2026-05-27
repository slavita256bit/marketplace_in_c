#include "io.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <stdio_ext.h>
#include <termios.h>
#include <unistd.h>
#endif

// Открытие файла с обработкой ошибок
FILE* open_file(char *filename, bool binary, bool write_mode, bool exit_on_fail)
{
    FILE* file = fopen(filename, (binary ? (write_mode ? "wb" : "rb") : (write_mode ? "w" : "r")));

    if (file == NULL)
    {
        printf(SET_RED "Cannot open file %s!\n" RESET, filename);
        if (exit_on_fail) exit(0);
    }

    return file;
}

// Ввод целого числа в заданном диапазоне
int read_int_range(int from, int to)
{
    bool first_iteration = true;
    int x;
    do
    {
        if (!first_iteration) printf("Invalid format! Enter a number (from %d to %d): ", from, to);
        x = read_int(stdin, false);
        first_iteration = false;
    } while (x < from || x > to);
    return x;
}

// Ввод целого числа
int read_int(FILE* file, bool binary)
{
    flush_buffer(file, true);
    int x;
    if (binary)
        fread(&x, sizeof(int), 1, file);
    else
        while (fscanf(file, "%d", &x) == 0)
        {
            printf(SET_RED "Invalid input! Expected an integer: " RESET);
            flush_buffer(file, true);
        }
    return x;
}

// Ввод вещественного числа
float read_float(FILE* file, bool binary)
{
    flush_buffer(file, true);
    float x;
    if (binary)
        fread(&x, sizeof(float), 1, file);
    else
        while (fscanf(file, "%f", &x) == 0)
        {
            printf(SET_RED "Invalid input! Expected a float: " RESET);
            flush_buffer(file, true);
        }
    return x;
}

// Ввод строки
void read_string(char* str, FILE* file, bool until_ln)
{
    flush_buffer(file, true);
    fscanf(file, (until_ln ? "%[^\n]" : "%s"), str);
}

// Очистка буфера ввода
void flush_buffer(FILE* file, bool stdin_only)
{
    if (!stdin_only || file == stdin)
    {
#ifdef _WIN32
        rewind(file);
#else
        __fpurge(file);
#endif
    }
}

// Вывод символа n раз
void print_n_times(int n, char c)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}

// Очистка экрана
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
