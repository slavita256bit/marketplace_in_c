#include "product.h"
#include "io.h"
#include "stack.h"
#include "tree.h"
#include "image.h"
#include "categories.h"
#include <string.h>

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

Product read_new_product(int new_id, int images_count)
{
	Product product;
	product.id = new_id;
	printf("Название: ");
	read_string(product.name, stdin, true);
	printf("Описание: ");
	read_string(product.description, stdin, true);
	printf("Цена: ");
	product.cost = read_int(stdin, false);
	printf("Рейтинг (от 1 до %d): ", MAX_RATING);
	product.rating = read_int_range(1, MAX_RATING);
	printf("ID картинки: ");
	product.image_id = read_int_range(0, images_count - 1);
	printf("ID категории: ");
	product.cs.category_id = read_int(stdin, false);

	Category cat = get_category(product.cs.category_id);
	for (int i = 0; i < cat.fields_count; i++)
	{
		printf("%s: ", cat.field_names[i]);

		if (cat.field_types[i] == INT)
			product.cs.fields[i].number = read_int(stdin, false);

		else if (cat.field_types[i] == FLOAT)
			product.cs.fields[i].real = read_float(stdin, false);

		else if (cat.field_types[i] == STR)
			read_string(product.cs.fields[i].str, stdin, true);
	}

	return product;
}

void print_rating(char* buffer, int rating)
{
	char* ptr = buffer;
	if (rating <= 2) ptr += sprintf(ptr, "%s", SET_RED);
	else if (rating == 3) ptr += sprintf(ptr, "%s", SET_YELLOW);
	else ptr += sprintf(ptr, "%s", SET_GREEN);

	for (int i = 0; i < rating; i++) ptr += sprintf(ptr, "*");
	for (int i = rating; i < MAX_RATING; i++) ptr += sprintf(ptr, " ");

	sprintf(ptr, "%s", RESET);
}

void print_products_header()
{
	printf(SET_BLUE);
	printf("%-*s %-2s %-*s %-*s %-5s %-10s \n",
			CARD_WIDTH, "Картинка", "ID", MAX_LENGTH, "Название", MAX_LENGTH, "Категория", "Цена", "Рейтинг");
	printf(RESET "\n");
}

// Вывод одного товара в виде строки таблицы
void print_product_row(Product product, Image* images)
{
	Category category = get_category(product.cs.category_id);

	char rating_str[MAX_LENGTH];
	print_rating(rating_str, product.rating);

	printf("%-*s %-2d %-*s %-*s %-5d %-10s \n",
			CARD_WIDTH, images[product.image_id].symbols[0], product.id, MAX_LENGTH, product.name, MAX_LENGTH, category.name, product.cost, rating_str);

	for (int i = 1; i < CARD_HEIGHT; i++)
		printf("%*s\n", CARD_WIDTH, images[product.image_id].symbols[i]);
}

// Вывод большой карточки товара с картинкой
void print_product_details(Product product, Image* images)
{
	char info[CARD_HEIGHT][DESCRIPTION_LENGTH] = {0};
	int lines = 0;
	Category category = get_category(product.cs.category_id);

	sprintf(info[lines++], "ID: %d", product.id);
	sprintf(info[lines++], "Название: %s", product.name);
	sprintf(info[lines++], "Категория: %s", category.name);
	sprintf(info[lines++], "Цена: %d", product.cost);

	char rating_str[DESCRIPTION_LENGTH];
	print_rating(rating_str, product.rating);
	strcpy(info[lines++], rating_str);

	print_n_times(CARD_WIDTH + DESCRIPTION_LENGTH + 3, '=');
	printf("\n");

	for (int i = 0; i < CARD_HEIGHT; i++)
	{
		printf("%s", images[product.image_id].symbols[i]);
		print_n_times(CARD_WIDTH - strlen(images[product.image_id].symbols[i]), ' ');

		if (i < lines)
			printf(" | %s\n", info[i]);
		else
			printf(" |\n");
	}

	printf("\nОписание:\n%s\n", product.description);
	print_n_times(CARD_WIDTH + DESCRIPTION_LENGTH + 3, '=');
	printf("\n");

	for (int i = 0; i < category.fields_count; i++)
		print_category_field(category, product.cs, i);
}
