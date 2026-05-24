#include "image.h"

#include "product.h"

Image* import_images(char *filename, int *n)
{
	FILE* file = open_file(filename, false, false, true);

	Image* images = calloc(*n, sizeof(Image));
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < CARD_HEIGHT; j++)
			read_string(images[i].symbols[j], file, true);

	fclose(file);

	return images;
}