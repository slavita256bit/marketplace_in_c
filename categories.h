#pragma once
#include "settings.h"

typedef struct Characteristics Characteristics;

enum Type
{
    INT,
    FLOAT,
    STR,
};
typedef enum Type Type;

struct Category
{
    char name[MAX_LENGTH];
    int fields_count;
    Type field_types[MAX_FIELD_COUNT];
    char field_names[MAX_FIELD_COUNT][MAX_LENGTH];
};
typedef struct Category Category;

Category read_new_category();
int get_categories_count();

void add_category(Category category);
Category get_category(int index);

void print_available_categories();
void print_category_field(Category category, Characteristics cs, int i);