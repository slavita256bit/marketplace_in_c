#pragma once
#include <stdbool.h>

enum State {
    MENU = 'm',
    ADD_PRODUCT = 'a',
    ADD_CATEGORY = 'c',
    IMPORT_PRODUCTS = 'i',
    EXPORT_PRODUCTS = 'e',
    LIST_PRODUCTS = 'l',
    VIEW_PRODUCT = 'v',
};
typedef enum State State;

char ask_action(const char* acceptable_chars);                      // Спрашивает пользователя о текущем действии
void read_string_or_default(char* out, const char* default_string); // Ввод строки или установка значения по умолчанию
char wait_special_symbol(bool esc, bool enter);                     // Ожидание ввода специального символа