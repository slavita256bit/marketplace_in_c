#include "product.h"
#include "io.h"
#include "stack.h"

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
	FILE* file = fopen(filename, "a");
	int count = ftell(file) / sizeof(Category);
	fclose(file);
	return count;
}

Category* get_category(char *filename, int index)
{
	//todo fseek and fread
}

void add_category(char *filename, Category category)
{
	//todo check
	FILE* file = fopen(filename, "ab");
	fwrite(&category, sizeof(Category), 1, file);
	fclose(file);
}

Product read_new_product(int new_id)
{
	Product product;
	printf("Название: ");
	read_string(product.name, stdin, true);

	//todo
}

void print_card_short(Product product)
{
	//todo
	// + image + category parsing
	printf("%s %d %d", product.name, product.cost, product.rating);
}

void print_card_big(Product product)
{
	//todo
	printf("%s %d %s %d", product.name, product.cost, product.description, product.rating);
}