#pragma once
#include "settings.h"

typedef struct TreeNode TreeNode;
typedef struct Image Image;
typedef struct ProductStack ProductStack;

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
    int image_id;
    char name[MAX_LENGTH];
    char description[DESCRIPTION_LENGTH];
    int cost;
    int rating;
    Characteristics cs;
};
typedef struct Product Product;

void import_products(TreeNode** products, char* filename);
void export_products(TreeNode* products, char* filename);
Product read_new_product(int new_id, int images_count);

void print_rating(char* buffer, int rating);

void print_products_header();
void print_product_row(Product product, Image* images);
void print_product_details(Product product, Image* images);