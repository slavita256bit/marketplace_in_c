#pragma once
#include <stdio.h>

int read_int(FILE* file, bool binary);
void print_int(int x, FILE* file, bool binary);
void read_string(char* str, FILE* file, bool until_ln);
void flush_buffer(FILE* file);