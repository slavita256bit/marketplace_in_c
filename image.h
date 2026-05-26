#pragma once
#include "settings.h"
#include "io.h"
#include "malloc.h"
#include <stdbool.h>

typedef struct Image Image;
struct Image
{
    char symbols[CARD_HEIGHT][CARD_WIDTH];
};

Image* import_images(int* n);
void print_available_images(Image* images, int images_count);