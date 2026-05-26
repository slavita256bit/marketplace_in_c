#include "interaction.h"
#include "io.h"
#include <string.h>
#include <conio.h>

#include "settings.h"

void print_ask_chars(const char* acceptable_chars)
{
    printf("Введите действие (");
    int n = strlen(acceptable_chars);
    for (int i = 0; i < n - 1; i++)
        printf("%c/", acceptable_chars[i]);
    printf("%c", acceptable_chars[n - 1]);
    printf("): ");
}

char ask_action(const char* acceptable_chars)
{
    print_ask_chars(acceptable_chars);

    char answer;
    bool valid_char = false;
    do
    {
        flush_buffer(stdin, true);
        //scanf_s("%c", &answer, 1);
        answer = _getch();
        printf("%c\n", answer);
        valid_char = (strchr(acceptable_chars, answer) == NULL);
        if (valid_char)
            print_ask_chars(acceptable_chars);
    }
    while (valid_char);

    return answer;
}

char wait_special_symbol(bool esc, bool enter)
{
    char answer;
    do
    {
        flush_buffer(stdin, true);
        answer = _getch();
    } while (!((esc && answer == ESC) || (esc && answer == ESC_R) || (enter && answer == ENTER)));
    return answer;
}

void read_string_or_default(char* out, const char* default_string)
{
    flush_buffer(stdin, true);
    fgets(out, FILENAME_MAX, stdin);
    if (out[0] == '\n')
    {
        strcpy(out, default_string);
        return;
    }
    out[strcspn(out, "\n")] = '\0';
}