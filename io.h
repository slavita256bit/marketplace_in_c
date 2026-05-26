#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SET_RED "\x1B[31m"
#define SET_GREEN "\x1B[32m"
#define SET_YELLOW "\x1B[33m"
#define SET_BLUE "\x1B[34m"
#define RESET "\x1B[0m"

#define ESC '\033'
#define ESC_R '\177'
#define ENTER '\n'
#define ALL_SPECIAL_CHARS "\033\r"

FILE* open_file(char* filename, bool binary, bool write_mode, bool exit_on_fail);
int read_int_range(int from, int to);
int read_int(FILE* file, bool binary);
float read_float(FILE* file, bool binary);
void read_string(char* str, FILE* file, bool until_ln);
void clear_screen();
void flush_buffer(FILE* file, bool stdin_skip);
void print_n_times(int n, char c);