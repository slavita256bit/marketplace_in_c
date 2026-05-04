#pragma once
#include "settings.h"

enum Type
{
    INT,
    FLOAT,
    STR,
};
typedef enum Type Type;

struct Catergory
{
    char name[MAX_LENGTH];
    Type field_types[MAX_FIELD_COUNT];
};

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
    int image_id;
    char name[MAX_LENGTH];
    char description[DESCRIPTION_LENGTH];
    int cost;
    int rating; //сделать цветные звёздочки
    Characteristics cs;
};

