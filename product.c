#include "product.h"
#include "io.h"
#include "stack.h"
#include "tree.h"
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

Product read_new_product(int new_id)
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

void print_rating(int rating)
{
	if (rating <= 2) printf(SET_RED);
	else if (rating == 3) printf(SET_YELLOW);
	else printf(SET_GREEN);

	for (int i = 0; i < rating; i++) printf("*");
	for (int i = rating; i < MAX_RATING; i++) printf(" ");

	printf(RESET);
}

void print_products_header()
{
	printf(SET_BLUE);
	printf("%-2s %-*s %-*s %-5s %-10s \n",
			"ID", MAX_LENGTH, "Название", MAX_LENGTH, "Категория", "Цена", "Рейтинг");
	printf(RESET "\n");
}

// Вывод одного товара в виде строки таблицы
void print_product_row(Product product)
{
	Category category = get_category(product.cs.category_id);

	printf("%-2d %-*s %-*s %-5d",
			product.id, MAX_LENGTH, product.name, MAX_LENGTH, category.name, product.cost);

	print_rating(product.rating);
	printf("\n");
}

// Вывод большой карточки товара с картинкой
void print_product_details(Product product)
{
	Category category = get_category(product.cs.category_id);

	printf("ID: %d\n", product.id);
	printf("Название: %s\n", product.name);
	printf("Категория: %s\n", category.name);
	printf("Цена: %d\n", product.cost);

	printf("\nОписание:\n%s\n", product.description);

	print_rating(product.rating);
	printf("\n");

	for (int i = 0; i < category.fields_count; i++)
	{
		print_category_field(category, product.cs, i);
		printf("\n");
	}
}
