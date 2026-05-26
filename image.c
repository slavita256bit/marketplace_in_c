#include "image.h"
#include "product.h"

Image* import_images(int *n)
{
	FILE* file = open_file(IMAGES_FILENAME, false, false, true);

	(*n) = read_int(file, false);
	fgetc(file);

	Image* images = calloc(*n, sizeof(Image));
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < CARD_HEIGHT; j++)
		{
			read_string(images[i].symbols[j], file, true);
			fgetc(file);
		}

	fclose(file);

	return images;
}

void print_available_images(Image* images, int images_count)
{
	printf("\nДоступные картинки:\n");
	for (int i = 0; i < images_count; i++)
	{
		printf("ID: %d\n", i);
		for (int j = 0; j < CARD_HEIGHT; j++)
			printf("%s\n", images[i].symbols[j]);
		printf("\n");
	}
}
