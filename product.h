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

void import_products(TreeNode** products, char* filename);
void export_products(TreeNode* products, char* filename);
Product read_new_product(int new_id);

void print_rating(int rating);

void print_products_header();
void print_product_row(Product product, int index);
void print_product_details(Product product);