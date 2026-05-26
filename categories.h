#pragma once

typedef struct Category Category;
typedef struct Characteristics Characteristics;

Category read_new_category();
int get_categories_count();

void add_category(Category category);
Category get_category(int index);

void print_available_categories();
void print_category_field(Category category, Characteristics cs, int i);