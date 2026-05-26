#include "categories.h"
#include "product.h"
#include "io.h"

int get_categories_count()
{
    FILE* file = fopen(CATEGORIES_FILENAME, "rb");
    if (file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int count = ftell(file) / sizeof(Category);
    fclose(file);

    return count;
}

void add_category(Category category)
{
    FILE* file = fopen(CATEGORIES_FILENAME, "ab");
    if (file == NULL)
    {
        printf("Failed to open file %s to add category.\n", CATEGORIES_FILENAME);
        exit(0);
    }

    fwrite(&category, sizeof(Category), 1, file);
    fclose(file);
}

Category get_category(int index)
{
    Category category;
    FILE* file = open_file(CATEGORIES_FILENAME, true, false, true);
    fseek(file, index * sizeof(Category), SEEK_SET);
    fread(&category, sizeof(Category), 1, file);
    fclose(file);
    return category;
}

void print_available_categories()
{
    int categories_count = get_categories_count();
    printf("\nAvailable categories:\n");
    for (int i = 0; i < categories_count; i++)
        printf("%d - %s\n", i, get_category(i).name);
    printf("\n");
}

Category read_new_category()
{
    Category category;
    printf("Category name: ");
    read_string(category.name, stdin, true);

    printf("Number of additional fields (up to %d): ", MAX_FIELD_COUNT);
    category.fields_count = read_int_range(0, MAX_FIELD_COUNT);

    for (int i = 0; i < category.fields_count; i++)
    {
        printf("Field %d name: ", i + 1);
        read_string(category.field_names[i], stdin, true);
        printf("Field type (0 - Integer, 1 - Float, 2 - String): ");
        category.field_types[i] = (Type)read_int_range(0, 2);
    }
    return category;
}

void print_category_field(Category category, Characteristics cs, int i)
{
    if (category.field_types[i] == INT)
        printf("%s: %d", category.field_names[i], cs.fields[i].number);

    if (category.field_types[i] == STR)
        printf("%s: %s", category.field_names[i], cs.fields[i].str);

    if (category.field_types[i] == FLOAT)
        printf("%s: %.2f", category.field_names[i], cs.fields[i].real);
}