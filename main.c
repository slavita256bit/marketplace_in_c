#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "interaction.h"
#include "product.h"
#include "stack.h"

int main(void)
{
    char products_filename[FILENAME_MAX];
    int images_count = 0;
    Image* images = import_images(IMAGES_FILENAME, &images_count);
    TreeNode* products = NULL, *current_product = NULL;

    State state = MENU;
    do
    {
        clear_screen();

        switch (state)
        {
        case MENU:
            printf("i - Импортировать товары\n");
            printf("a - Добавить товар\n");
            if (products == NULL)
                printf("l - Каталог товаров\n");
            printf("x - Выйти\n");

            state = ask_action(products == NULL ? "iax" : "ialx");
            break;

        case IMPORT_PRODUCTS:
            printf("Введите имя файла для импорта товаров: ");
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);
            int prev_products_count = tree_get_size(products);
            import_products(&products, products_filename);
            int products_count = tree_get_size(products);
            printf("Импортировано %d товаров, всего товаров %d.", products_count - prev_products_count, products_count);
            break;

        case ADD_PRODUCT:
            Product product = read_new_product(products_count);
            tree_add_element(&products, product);
            break;

        case EXPORT_PRODUCTS:
            printf("Введите имя файла для экспорта товаров: ");
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);
            export_products(products, products_filename);
            printf("Товары записаны в файл!");
            break;

        case LIST_PRODUCTS:
            tree_print_symmetric(products, images, /*sorted -> by rating -> ask direction*/);

            // filter by category (mb with tree)

            printf("Нажмите Enter для просмотра товара, Esc для выхода в меню.\n");
            if (wait_special_symbol(true, true) == ENTER)
            {
                printf("Выберите номер товара для просмотра.\n");
                current_product = tree_find(products, read_int_range(0, products_count - 1));
                state = VIEW_PRODUCT;
            }
            else
                state = MENU;

            break;

        case VIEW_PRODUCT:
            print_card_big(current_product->item);

            printf("Нажмите Enter чтобы оценить товар, Esc для списка товаров.\n");

            if (wait_special_symbol(true, true) == ENTER)
            {
                printf("Оцените товар.\n");
                current_product->item.rating = read_int_range(0, MAX_RATING);
                state = VIEW_PRODUCT;
            }
            else
                state = MENU;
            break;
        }

        if (state != MENU && state != LIST_PRODUCTS)
        {
            printf("Нажмите Esc для выхода в меню.");
            wait_special_symbol(true, false);
            state = MENU;
        }
    } while (state != 'x');

    return 0;
}
