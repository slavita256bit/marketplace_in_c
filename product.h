#pragma once
#include "settings.h"

typedef struct TreeNode TreeNode;

union Field
{
    int number;
    float real;
    char str[MAX_LENGTH];
};
typedef union Field Field;

struct Characteristics
{
    int category_id;
    Field fields[MAX_FIELD_COUNT];
};
typedef struct Characteristics Characteristics;

struct Product
{
    int id;
    char name[MAX_LENGTH];
    char description[DESCRIPTION_LENGTH];
    int cost;
    int rating;
    Characteristics cs;
};
typedef struct Product Product;

void import_products(TreeNode** products, char* filename); // Импорт товаров из файла
void export_products(TreeNode* products, char* filename);  // Экспорт товаров в файл
Product read_new_product(int new_id);                      // Ввод данных нового товара

void print_rating(int rating);                             // Вывод рейтинга товара

void print_products_header();                              // Вывод шапки таблицы товаров
void print_product_row(Product product, int index);        // Вывод одного товара в виде строки таблицы
void print_product_details(Product product);               // Вывод большой карточки товара