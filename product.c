#include "product.h"
#include "io.h"
#include "stack.h"
#include "tree.h"
#include "image.h"

void import_products(TreeNode** products, char* filename)
{
	FILE* file = open_file(filename, true, false, false);
	if (file == NULL)
		return;

	while (!feof(file))
	{
		Product product;
		fread(&product, sizeof(Product), 1, file);
		tree_add_element(products, product);
	}

	fclose(file);
}

void export_products(TreeNode* products, char* filename)
{
	FILE* file = open_file(filename, true, true, false);
	if (file == NULL)
	{
		printf("Невозможно записать в файл %s", filename);
		return;
	}

	tree_save_direct(products, file);

	fclose(file);
}

int get_categories_count(char *filename)
{
	FILE* file = open_file(filename, true, false, true);
	if (file == NULL)
		return 0;

	fseek(file, 0, SEEK_END);
	int count = ftell(file) / sizeof(Category);
	fclose(file);

	return count;
}

Category get_category(char *filename, int index)
{
	Category category;
	FILE* file = open_file(filename, true, false, true);
	fseek(file, index * sizeof(Category), SEEK_SET);
	fread(&category, sizeof(Category), 1, file);
	fclose(file);
	return category;
}

void add_category(char *filename, Category category)
{
	FILE* file = fopen(filename, "ab");
	if (file == NULL)
	{
		printf("Не удалось открыть файл %s для добавления категории.\n", filename);
		exit(0);
	}

	fwrite(&category, sizeof(Category), 1, file);
	fclose(file);
}

Product read_new_product(int new_id)
{
	Product product = {0};
	product.id = new_id;

	printf("Название: ");
	read_string(product.name, stdin, true);

	printf("Описание: ");
	read_string(product.description, stdin, true);

	printf("Цена: ");
	product.cost = read_int(stdin, false);

	product.rating = read_int_range(1, MAX_RATING);

	// Подумать как сделать лушче (мб выводить сразу картинки чтобы было видно)
	printf("ID картинки: ");
	product.image_id = read_int(stdin, false);

	printf("ID категории: ");
	product.cs.category_id = read_int(stdin, false);

	return product;
}

void print_rating(int rating)
{
	if (rating <= 2) printf(SET_RED);
	else if (rating == 3) printf(SET_YELLOW);
	else printf(SET_GREEN);

	for (int i = 0; i < rating; i++) printf("*");
	for (int i = rating; i < MAX_RATING; i++) printf(" ");

	printf(RESET);
}

void print_card_short(Product product, Image* images)
{
	print_n_times(CARD_WIDTH + 50, '=');
	printf("\n");

	for (int i = 0; i < CARD_HEIGHT; i++)
	{
		if (images != NULL)
			printf("%-*.*s", CARD_WIDTH, CARD_WIDTH, images[product.image_id].symbols[i]);
		else
			print_n_times(CARD_WIDTH, ' ');

		if (i == 1)
			printf(" | [ID: %d] %s", product.id, product.name);
		else if (i == 2)
			printf(" | Цена: %d ", product.cost);
		else if (i == 3)
		{
			printf(" | Отзывы: ");
			print_rating(product.rating);
		}
		else
			printf(" |");
		printf("\n");
	}
	print_n_times(CARD_WIDTH + 50, '=');
	printf("\n");
}

void print_card_big(Product product, Image* images)
{
	print_n_times(CARD_WIDTH + 50, '=');
	printf("\n");

	for (int i = 0; i < CARD_HEIGHT; i++)
	{
		if (images != NULL)
			printf("%-*.*s", CARD_WIDTH, CARD_WIDTH, images[product.image_id].symbols[i]);
		else
			print_n_times(CARD_WIDTH, ' ');

		//todo кринж
		if (i == 1) printf(" | ID: %d", product.id);
		else if (i == 2) printf(" | Название: %s", product.name);
		else if (i == 3) { printf(" | Рейтинг: "); print_rating(product.rating); }
		else if (i == 4) printf(" | Цена: %d", product.cost);
		else if (i == 5) printf(" | ID категории: %d", product.cs.category_id);
		else printf(" |");

		printf("\n");
	}

	printf("\nОписание:\n%s\n", product.description);
	print_n_times(CARD_WIDTH + 50, '=');
	printf("\n");
}