#include <locale.h>
#include <string.h>
#include "categories.h"
#include "interaction.h"
#include "io.h"
#include "product.h"
#include "stack.h"
#include "tree.h"

int main(void)
{
    char products_filename[FILENAME_MAX];
    TreeNode* products = NULL, *current_product = NULL;

    State state = MENU;
    do
    {
        clear_screen();

        State prev_state = state;
        switch (state)
        {
        case MENU:
            printf("i - Import products\n");
            printf("c - Add category\n");
            if (get_categories_count() > 0)
                printf("a - Add product\n");
            if (products != NULL)
            {
                printf("l - Product catalog\n");
                printf("e - Export products\n");
            }
            printf("x - Exit\n");

            state = ask_action(get_categories_count() > 0 ? (products != NULL ? "icalxe" : "icax") : "icx");
            break;

        case IMPORT_PRODUCTS:
        {
            printf("Enter filename to import products (Enter for %s): ", PRODUCTS_DEFAULT_FILENAME);
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);

            int prev_products_count = tree_get_size(products);
            import_products(&products, products_filename);
            int current_products_count = tree_get_size(products);

            printf(current_products_count - prev_products_count > 0 ? SET_GREEN : SET_RED);
            printf("Imported %d products, total products %d\n" RESET, current_products_count - prev_products_count, current_products_count);
            break;
        }

        case ADD_PRODUCT:
        {
            print_available_categories();
            Product product = read_new_product(tree_get_size(products));
            tree_add_element(&products, product); // todo add confirm in while
            printf(SET_GREEN "Product added!\n" RESET);
            break;
        }

        case ADD_CATEGORY:
        {
            Category cat = read_new_category();
            add_category(cat); // todo add confirm in while
            printf(SET_GREEN "Category successfully added!\n" RESET);
            break;
        }

        case EXPORT_PRODUCTS:
        {
            printf("Enter filename to export products (Enter for %s): ", PRODUCTS_DEFAULT_FILENAME);
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);
            export_products(products, products_filename);
            printf(SET_GREEN "Products saved to file!\n" RESET);
            break;
        }

        case LIST_PRODUCTS:
        {
            printf("Sorting by rating\n");
            printf("a - Ascending\n");
            printf("d - Descending\n");
            bool ascending = (ask_action("ad") == 'a');

            print_products_header();
            tree_card_print(products, ascending);

            // filter by category (mb with tree)

            printf("Press Enter to view a product, Esc to return to menu\n");
            if (wait_special_symbol(true, true) == ENTER)
            {
                printf("Enter the product index to view.\n");
                current_product = tree_find(products, read_int_range(0, tree_get_size(products) - 1));
                state = VIEW_PRODUCT;
            }
            else
                state = MENU;

            break;
        }

        case VIEW_PRODUCT:
        {
            print_product_details(current_product->item);

            printf("\nPress Enter to rate the product, Esc for product list.\n");

            if (wait_special_symbol(true, true) == ENTER)
            {
                printf("Rate the product from 1 to %d: ", MAX_RATING);
                current_product->item.rating = read_int_range(1, MAX_RATING);
                // Если после изменения рейтинга ломается BST (так как дерево строится по рейтингу),
                // позже мы будем дерево перестраивать, сейчас оставляем так.
                state = VIEW_PRODUCT;
            }
            else
                state = LIST_PRODUCTS;
            break;
        }
        }

        if (prev_state != MENU && prev_state != LIST_PRODUCTS)
        {
            printf("\nPress Esc to return to menu.");
            wait_special_symbol(true, false);
            state = MENU;
        }
    } while (state != 'x');

    tree_clear(&products);

    return 0;
}
