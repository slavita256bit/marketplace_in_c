#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "categories.h"
#include "image.h"
#include "interaction.h"
#include "product.h"
#include "stack.h"
#include "tree.h"

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    char products_filename[FILENAME_MAX];
    int images_count = 0;
    Image* images = import_images(&images_count);
    TreeNode* products = NULL, *current_product = NULL;

    State state = MENU;
    do
    {
        clear_screen();

        State prev_state = state;
        switch (state)
        {
        case MENU:
            printf("i - Импортировать товары\n");
            printf("c - Добавить категорию\n");
            if (get_categories_count() > 0)
                printf("a - Добавить товар\n");
            if (products != NULL)
            {
                printf("l - Каталог товаров\n");
                printf("e - Экспорт товаров\n");
            }
            printf("x - Выйти\n");

            state = ask_action(get_categories_count() > 0 ? (products != NULL ? "icalxe" : "icax") : "icx");
            break;

        case IMPORT_PRODUCTS:
            printf("Введите имя файла для импорта товаров (Enter для %s): ", PRODUCTS_DEFAULT_FILENAME);
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);

            int prev_products_count = tree_get_size(products);
            import_products(&products, products_filename);
            int products_count = tree_get_size(products);

            printf(products_count - prev_products_count > 0 ? SET_GREEN : SET_RED);
            printf("Импортировано %d товаров, всего товаров %d\n" RESET, products_count - prev_products_count, products_count);
            break;

        case ADD_PRODUCT:
            print_available_images(images, images_count);
            print_available_categories();
            Product product = read_new_product(products_count, images_count);
            tree_add_element(&products, product);
            printf(SET_GREEN "Товар добавлен!\n" RESET);
            break;

        case ADD_CATEGORY:
            Category cat = read_new_category();
            add_category(cat);
            printf(SET_GREEN "Категория успешно добавлена!\n" RESET);
            break;

        case EXPORT_PRODUCTS:
            printf("Введите имя файла для экспорта товаров (Enter для %s): ", PRODUCTS_DEFAULT_FILENAME);
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);
            export_products(products, products_filename);
            printf(SET_GREEN "Товары записаны в файл!\n" RESET);
            break;

        case LIST_PRODUCTS:
            printf("a - По возрастанию\n");
            printf("d - По убыванию\n");
            bool ascending = (ask_action("ad") == 'a');

            print_products_header();
            tree_card_print(products, images, ascending);

            // filter by category (mb with tree)

            printf("Нажмите Enter для просмотра товара, Esc для выхода в меню\n");
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
            print_product_details(current_product->item, images);

            printf("Нажмите Enter чтобы оценить товар, Esc для списка товаров.\n");

            if (wait_special_symbol(true, true) == ENTER)
            {
                printf("Оцените товар.\n");
                current_product->item.rating = read_int_range(1, MAX_RATING);
                // Если после изменения рейтинга ломается BST (так как дерево строится по рейтингу),
                // позже мы будем дерево перестраивать, сейчас оставляем так.
                state = VIEW_PRODUCT;
            }
            else
                state = MENU;
            break;
        }

        if (prev_state != MENU && prev_state != LIST_PRODUCTS)
        {
            printf("Нажмите Esc для выхода в меню.");
            wait_special_symbol(true, false);
            state = MENU;
        }
    } while (state != 'x');

    tree_clear(&products);
    free(images);

    return 0;
}
