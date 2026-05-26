#include "product.h"
#include "io.h"
#include "stack.h"
#include "tree.h"
#include "categories.h"
#include <string.h>

// Импорт товаров из файла
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

// Экспорт товаров в файл
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

// Ввод данных нового товара
Product read_new_product(int new_id)
{
	Product product;
	product.id = new_id;
	printf("Name: ");
	read_string(product.name, stdin, true);
	printf("Description: ");
	read_string(product.description, stdin, true);
	printf("Cost: ");
	product.cost = read_int(stdin, false);
	printf("Rating (from 1 to %d): ", MAX_RATING);
	product.rating = read_int_range(1, MAX_RATING);
	printf("Category ID: ");
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

// Вывод рейтинга товара
void print_rating(int rating)
{
	if (rating <= 2) printf(SET_RED);
	else if (rating == 3) printf(SET_YELLOW);
	else printf(SET_GREEN);

	for (int i = 0; i < rating; i++) printf("*");
	for (int i = rating; i < MAX_RATING; i++) printf(" ");

	printf(RESET);
}

// Вывод шапки таблицы товаров
void print_products_header()
{
	printf(SET_BLUE);
	printf("%-2s %-*s %-*s %-5s %-10s \n",
			"#", MAX_LENGTH, "Name", MAX_LENGTH, "Category", "Cost", "Rating");
	printf(RESET);
}

// Вывод одного товара в виде строки таблицы
void print_product_row(Product product, int index)
{
	Category category = get_category(product.cs.category_id);

	printf("%-2d %-*s %-*s %-5d ",
			index, MAX_LENGTH, product.name, MAX_LENGTH, category.name, product.cost);

	print_rating(product.rating);
	printf("\n");
}

// Вывод большой карточки товара
void print_product_details(Product product)
{
	Category category = get_category(product.cs.category_id);

	printf("ID: %d\n", product.id);
	printf("Name: %s\n", product.name);
	printf("Category: %s\n", category.name);
	printf("Cost: %d\n", product.cost);
	printf("Rating: ");
	print_rating(product.rating);
	printf("\n");

	printf("\nDescription:\n%s\n\n", product.description);

	for (int i = 0; i < category.fields_count; i++)
	{
		print_category_field(category, product.cs, i);
		printf("\n");
	}
}
